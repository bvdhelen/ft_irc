#ifndef COMMANDFACTORY_HPP
#define COMMANDFACTORY_HPP

#include "ft_irc.hpp"

#include "Command.hpp"

class CommandFactory
{
	public:
		static Command *createCommand(
			const std::string &commandName,
			const std::vector<std::string> &params);
};

#endif
