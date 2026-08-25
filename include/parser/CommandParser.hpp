#ifndef COMMANDPARSER_HPP
# define COMMANDPARSER_HPP

# include "ft_irc.hpp"
# include "Server.hpp"
# include "Client.hpp"

class CommandParser
{
	public:
		static void parseAndExecute(std::string line, Server &server, Client &client);
	private:
		static std::string parseCommandName(std::string &line);
		static void parseParams(std::string &line, std::vector<std::string> &params);
};

#endif
