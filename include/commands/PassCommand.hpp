#ifndef PASSCOMMAND_HPP
#define PASSCOMMAND_HPP

#include "commands/Command.hpp"
#include "Replies.hpp"

class PassCommand : public Command
{
	public:
		PassCommand(const std::vector<std::string>& params);
		~PassCommand();

		void execute(Server& server, Client& client);
};

#endif
