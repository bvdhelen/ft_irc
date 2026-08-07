#ifndef SERVER_HPP
#define SERVER_HPP

#include "ft_irc.hpp"

class Client;
class Channel;

class Server
{
	private:

		int _socket;
		int _port;
		std::string _password;
		bool _isRunning;

		//Conocer los clientes
		std::map<int, Client> _clients;

		//Conocer los canales
		std::map<std::string, Channel> _channels;

		//Vector de pollfds
		std::vector<struct pollfd> _pollfds;

		
	public:
		Server(int port, const std::string &password);
		~Server();

		//Inicializar [socket(), bind(), listen()]
		void initServer();

		//Bucle principal
		void run();

		Client *getClientBySocket(int socket);
		Client *getClientByNick(const std::string &nickToSearch);
		Channel *getChannelByName(const std::string &name);

		// void acceptClient(); //nuevo cliente
		// void disconnectClient(int fd); //desconectar cliente
		// void executeCommand(Client &, Command &); //ejecutar comandos
};

#endif
