#ifndef MODECOMMAND_HPP
#define MODECOMMAND_HPP

#include "commands/Command.hpp"

class ModeCommand : public Command
{
	private:
		void applyModes(Channel *channel, Client &client, Server &server, const std::string &modestring);
	public:
		ModeCommand(const std::vector<std::string> &params);
		~ModeCommand();

		void execute(Server &server, Client &client);
};

#endif
