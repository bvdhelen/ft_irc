#ifndef PINGCOMMAND_HPP
# define PINGCOMMAND_HPP

# include "Command.hpp"

class PingCommand : public Command
{
	public:
		PingCommand(const std::vector<std::string> &params);
		~PingCommand();

		void execute(Server &server, Client &client);
};

#endif
