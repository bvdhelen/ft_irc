#ifndef SERVER_HPP
#define SERVER_HPP

#include "ft_irc.hpp"
#include "Client.hpp"
#include "Channel.hpp"

class Server
{
	private:

		int _socket;
		int _port;
		std::string _password;
		static volatile sig_atomic_t _isRunning;
	
		//Conocer los clientes
		std::map<int, Client> _clients;

		//Conocer los canales
		std::map<std::string, Channel> _channels;

		//Vector de pollfds
		std::vector<struct pollfd> _pollfds;

		static void termination_handler(const int signal);
		void initSignals();
		void initSockets();

		void acceptClient(int serverfd);
		void disconnectClient(size_t& pollIndex);
		void receiveFromClient(size_t& pollIndex);
		void processData(std::string data, size_t pollIndex);
	public:

		Server(int port, const std::string &password);
		~Server();

		void initServer();
		void run();
		void closeServer();

		//Send
		void sendReplyToClient(int clientfd, int reply_number, const std::string &message);
		void sendToClient(Client *client, const std::string &message);
		void sendToChannel(Channel *channel, const std::string &message);
		void sendToChannelExcept(Channel *channel, Client *excluded, const std::string &message);

		//Getters (more can be done)
		const std::string& getPassword();
		const std::list<Client*> getAllClients();
		const std::list<Channel*> getAllChannels();
		Client *getClientBySocket(int socket);
		Client *getClientByNick(const std::string &nickToSearch);
		Channel *getChannelByName(const std::string &name);
		void removeChannel(const std::string &name);

		//Exceptions:
		class SocketFileDescriptorException : public std::exception
		{
			const char* what() const throw();
		};

		class BlockingSocketException : public std::exception
		{
			const char* what() const throw();
		};

		class BindAddressException : public std::exception
		{
			const char* what() const throw();
		};

		class ListenConnectionsException : public std::exception
		{
			const char* what() const throw();
		};

		class PollingFailedException : public std::exception
		{
			const char* what() const throw();
		};

};

#endif
