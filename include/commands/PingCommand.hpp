#ifndef PINGCOMMAND_HPP
# define PINGCOMMAND_HPP

#include "commands/Command.hpp"
#include "Replies.hpp"

class PingCommand : public Command
{
	public:
		PingCommand(std::vector<std::string> params);
		~PingCommand();

		void execute(Server& server, Client& client);
};

#endif
