#ifndef USERCOMMAND_HPP
#define USERCOMMAND_HPP

#include "commands/Command.hpp"
#include "Replies.hpp"

class UserCommand : public Command
{
	public:
		UserCommand(const std::vector<std::string>& params);
		~UserCommand();

		void execute(Server& server, Client& client);
};

#endif
