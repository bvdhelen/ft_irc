#ifndef INVITE_COMMAND_HPP
# define INVITE_COMMAND_HPP

# include "Replies.hpp"
# include "Command.hpp"
# include "Channel.hpp"

/**
 * Command: INVITE
 * Parameters: <nickname> <channel>
 */
class InviteCommand : public Command
{
    public:
		InviteCommand(const std::vector<std::string> &params);
		~InviteCommand();

        void execute(Server &server, Client &client);
};

#endif
