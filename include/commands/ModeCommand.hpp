#ifndef MODECOMMAND_HPP
#define MODECOMMAND_HPP

#include "commands/Command.hpp"

class ModeCommand : public Command
{
	public:
		ModeCommand(const std::vector<std::string> &params);
		~ModeCommand();
		void execute(Server &server, Client &client);
};

#endif
