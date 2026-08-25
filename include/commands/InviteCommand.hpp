#ifndef INVITE_COMMAND_HPP
# define INVITE_COMMAND_HPP

# include "Command.hpp"

class InviteCommand : public Command
{
    public:
		InviteCommand(const std::vector<std::string> &params);
		~InviteCommand();

        void execute(Server &server, Client &client);
};

#endif
