#include "Server.hpp"
#include "parser/CommandParser.hpp"


volatile sig_atomic_t Server::_isRunning = false;

//Lo siento Izhan, los signal handlers van siempre arriba.
void Server::termination_handler(const int signal)
{
	Server::_isRunning = false;
	(void)signal;
}

Server::Server(int port, const std::string &password): _socket(-1), _port(port), _password(password)
{
}

Server::~Server()
{
}

void Server::initServer()
{
	initSignals();
	initSockets();
}

//Note: sigaction() can fail, but only when invalid parameters are sent. This is obviously not the case
//Therefore, no exception exists about signals.
void Server::initSignals()
{
	struct sigaction signal;
	sigset_t sigset;
	sigemptyset(&sigset);
	signal.sa_mask = sigset;
	signal.sa_flags = 0;
	signal.sa_handler = Server::termination_handler;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGTERM, &signal, NULL);
}

void Server::initSockets()
{
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket < 0)
		throw Server::SocketFileDescriptorException();

	int valueToSet = 1;
	//Setsockopt is to be able to reuse a port.
	setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &valueToSet, sizeof(valueToSet));

	if (fcntl(_socket, F_SETFL, O_NONBLOCK) < 0)
	{
		close(_socket);
		throw Server::BlockingSocketException();
	}

	struct sockaddr_in sck;
	sck.sin_family = AF_INET; //IPv4
	sck.sin_port = htons(_port);
	sck.sin_addr.s_addr = INADDR_ANY; //Anyone can write to the socket.

	if (bind(_socket,(const struct sockaddr *)&sck, sizeof(sck)) < 0)
	{
		close(_socket);
		throw Server::BindAddressException();
	}

	if (listen(_socket, SOMAXCONN) < 0) //SOMAXCONN calculates the maximum connections a socket can handle.
	{
		close(_socket);
		throw Server::ListenConnectionsException();
	}

	struct pollfd server_pfd;
	server_pfd.fd = _socket;
	server_pfd.events = POLLIN;
	server_pfd.revents = 0;
	_pollfds.push_back(server_pfd);
}

//The printed message it's usefull to know when the server is ready. But it not mandatory.
void Server::run()
{
	Server::_isRunning = true;
	std::cout << "IRC Server is now working!" << std::endl;
	while(Server::_isRunning)
	{
		int activity = poll(_pollfds.data(), _pollfds.size(), -1);

		if (activity < 0)
		{
			//Poll can be interrupted by signals, in which case sets errno to EINTR.
			if (errno == EINTR)
				continue;
			throw Server::PollingFailedException();
		}

		for (size_t i = 0; i < _pollfds.size(); i++)
		{
			//POLLERR, POLLHUP, POLLNVAL indicate that a socket has an error or disconnected.
			if (_pollfds[i].revents & (POLLERR | POLLHUP | POLLNVAL))
			{
				if (_pollfds[i].fd == _socket)
					throw Server::PollingFailedException();
				disconnectClient(i);
			}
			else if (_pollfds[i].revents & POLLIN)
			{
				if (_pollfds[i].fd == _socket)
					acceptClient(_pollfds[i].fd);
				else
					receiveFromClient(i);
			}
		}
	}
	std::cout << "Shutting down cleanly..." << std::endl;
	closeServer();
}
void Server::acceptClient(int serverfd)
{
	struct sockaddr_in clientSck;
	clientSck.sin_family = AF_INET;
	clientSck.sin_addr.s_addr = INADDR_ANY;
	socklen_t socketLength = sizeof(clientSck);
	int clientSocket = accept(serverfd, (struct sockaddr *)&clientSck, &socketLength);
	if (clientSocket < 0)
	{
		std::cout << "A client has been rejected." << std::endl;
		return;
	}

	if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) < 0)
	{
		close(clientSocket);
		return;
	}

	struct pollfd server_pfd;
	server_pfd.fd = clientSocket;
	server_pfd.events = POLLIN;
	server_pfd.revents = 0;
	_pollfds.push_back(server_pfd);

	_clients.insert(std::pair<int, Client>(clientSocket, Client(clientSocket)));
	Client *client = getClientBySocket(clientSocket);
    if (client != NULL)
		client->setHost(inet_ntoa(clientSck.sin_addr));
	std::cout << "A client has been accepted." << std::endl;
}

/**
 * Uses recv to receive the message from the client, bytesRead tells the number of bytes.
 * If bytesRead is more than 0, a message has been received and should be processed.
 * If its exactly 0 bytes, it means the client has disconnected.
 * If its -1, an error has ocurred.
 */
void Server::receiveFromClient(size_t& pollIndex)
{
	char buffer[512];
	ssize_t bytesRead;

	bytesRead = recv(_pollfds[pollIndex].fd, buffer, sizeof(buffer) - 1, 0);
	if (bytesRead == -1)
	{
		//recv can fail because there was just no message to read.
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return;
		//if its other error, then its serious
		disconnectClient(pollIndex);
	}
	else if (bytesRead == 0)
		disconnectClient(pollIndex);
	else
	{
		buffer[bytesRead] = '\0';
		processData(buffer, pollIndex);
	}
}

//Esta función desconecta a clientes...
//¿Debe encargarse de desconectarlos de todos los canales primero.
//¿Deberia la clase client tener una función disconnect?
void Server::disconnectClient(size_t& pollIndex)
{
	int clientfd = _pollfds[pollIndex].fd;
	Client* client = getClientBySocket(clientfd);
	client->disconnect();
	close(clientfd);
	std::cout << "A client disconected." << std::endl;
	//Erase from Server data structures.
	_clients.erase(clientfd);
	_pollfds.erase(_pollfds.begin() + pollIndex);
	pollIndex--;
}

void Server::processData(std::string data, size_t& pollIndex)
{
    Client * client = getClientBySocket(_pollfds[pollIndex].fd);
	client->appendBuffer(data);
	while (client->hasCommandBuffer())
	{
		std::string command = client->getCommandFromBuffer();
		CommandParser::parseAndExecute(command, *this, *client);


		//Después de ejecutar cada comando, revisar si el cliente debe desconectarse.
		if (client->hasRequestedDisconnection())
		{
			disconnectClient(pollIndex);
			return;
		}
	}	
}


void Server::sendReplyToClient(Client *client, int reply_number, const std::string& message, const std::string& command_name)
{
    std::stringstream ss;
    ss << ":ft_irc ";
    
    // Rellenar con ceros a la izquierda si tiene menos de 3 cifras
    if (reply_number < 10) ss << "00";
    else if (reply_number < 100) ss << "0";
    ss << reply_number << " ";

	if (!client->getHasNick())
		ss << "* ";
	else
		ss << client->getNickname() << " ";
	if (command_name != "")
		ss << command_name << " ";
	ss << ":" << message << "\r\n";

    std::string fullMessage = ss.str();

	sendReplyToClientRaw(client, fullMessage);
}

void Server::sendReplyToClientRaw(Client *client, const std::string& messageRaw)
{
	if (send(client->getSocket(), messageRaw.c_str(), messageRaw.length(), 0) < 0)
		client->setRequestedDisconnection(true);
}

void Server::sendToChannelRaw(Channel *channel, const std::string &messageRaw)
{
	if (channel == NULL)
		return ;
	const std::set<Client*>& clients = channel->getClients();
	std::set<Client *>::const_iterator it = clients.begin();

	for(; it != clients.end(); it++)
	{
		Client *client = *it;
		sendReplyToClientRaw(client, messageRaw);
	}
}

void Server::sendToChannelExceptRaw(Channel *channel, Client *clientExcept, const std::string &messageRaw)
{
	if (channel == NULL || clientExcept == NULL)
		return ;
	const std::set<Client*>& clients = channel->getClients();
	std::set<Client *>::const_iterator it = clients.begin();

	for(; it != clients.end(); it++)
	{
		Client *client = *it;
		if (client == clientExcept)
			continue;
		sendReplyToClientRaw(client, messageRaw);
	}
}

const std::string &Server::getPassword()
{
	return _password;
}

const std::list<Client *> Server::getAllClients()
{
	std::list<Client*> clients;

	std::map<int, Client>::iterator it = _clients.begin();

	for(; it != _clients.end(); it++)
	{
		clients.push_back(&(it->second));
	}
	return clients;
}

const std::list<Channel*> Server::getAllChannels()
{
	std::list<Channel*> channels;

	std::map<std::string, Channel>::iterator it = _channels.begin();

	for (; it != _channels.end(); it++)
	{
		channels.push_back(&(it->second));
	}
	return channels;
}

Client *Server::getClientBySocket(int socket)
{
    std::map<int, Client>::iterator it = _clients.find(socket);
    if (it != _clients.end())
        return &(it->second);
    return NULL;
}

Client *Server::getClientByNick(const std::string &nickToSearch)
{
    std::map<int, Client>::iterator it = _clients.begin();
    std::map<int, Client>::iterator end = _clients.end();

    for (; it != end; ++it)
    {
        if (it->second.getNickname().compare(nickToSearch) == 0)
    		return &(it->second);
    }
    return NULL;
}

Channel *Server::getChannelByName(const std::string &name)
{
    std::map<std::string, Channel>::iterator it = _channels.find(name);
    if (it != _channels.end())
        return &(it->second);
    return NULL;
}

//TODO: Envíar mensaje a cliente con algo parecido a "Connection closed by server"
void Server::closeServer()
{
	for(size_t i = 0; i < _pollfds.size(); i++)
	{
		Client *client = getClientBySocket(_pollfds[i].fd);
		if (client == NULL)
			continue;
		client->disconnect();
		close(client->getSocket());
	}
	close(_socket);
}

//Exceptions:
const char* Server::SocketFileDescriptorException::what() const throw()
{
	return "Couldn't create a file descriptor for the socket. (socket() failed)";
}

const char* Server::BlockingSocketException::what() const throw()
{
	return "Couldn't mark the socket as non-blocking. (fctnl() failed)";
}

const char* Server::BindAddressException::what() const throw()
{
	return "Couldn't assign address (port) for file descriptor of the socket. (bind() failed)";
}

const char* Server::ListenConnectionsException::what() const throw()
{
	return "Socket couldn't be used to listen incoming connections. (listen() failed)";
}

const char* Server::PollingFailedException::what() const throw()
{
	return "Polling of sockets failed. (poll() failed)";
}
