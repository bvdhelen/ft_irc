#ifndef PASSCOMMAND_HPP
# define PASSCOMMAND_HPP

# include "Command.hpp"

class PassCommand : public Command
{
	public:
		PassCommand(const std::vector<std::string> &params);
		~PassCommand();

		void execute(Server &server, Client &client);
};

#endif
