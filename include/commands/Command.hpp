#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "../ft_irc.hpp"

class Server;
class Client;

class Command
{
    protected:
        std::vector<std::string> _params;
    public:
		Command();
		virtual ~Command();

		const std::vector<std::string> &getParams() const;

        virtual void execute(Server &server, Client &client) = 0;
};

#endif