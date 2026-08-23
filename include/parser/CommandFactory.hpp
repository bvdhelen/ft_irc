#ifndef COMMANDFACTORY_HPP
#define COMMANDFACTORY_HPP

#include "ft_irc.hpp"

#include "commands/Command.hpp"

class CommandFactory
{
	public:
		static Command *createCommand(
			std::string commandName,
			const std::vector<std::string> &params);
};

#endif
