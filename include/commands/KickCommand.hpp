#ifndef KICK_COMMAND_HPP
# define KICK_COMMAND_HPP

# include "Replies.hpp"
# include "Command.hpp"
# include "Channel.hpp"

/**
 * Command: KICK
 * Parameters: <channel> <user> [<comment>]
 */
class KickCommand : public Command
{
    private:
        void kickClient(Server &server, Client &client, const std::string &channelName, const std::string &nickname);
	public:
		KickCommand(const std::vector<std::string> &params);
		~KickCommand();

		void execute(Server &server, Client &client);
};

#endif
