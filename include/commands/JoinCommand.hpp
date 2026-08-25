#ifndef JOINCOMMAND_HPP
# define JOINCOMMAND_HPP

# include "Replies.hpp"
# include "Command.hpp"
# include "Channel.hpp"

class JoinCommand : public Command
{
    private:
        std::vector<std::string> splitChannels(const std::string &channels);
        void handleJoinChannel(Server &server, Client &client, Channel *channel, const std::string& channelName);
    public:
        JoinCommand(const std::vector<std::string> &params);
        ~JoinCommand();
        
        void execute(Server &server, Client &client);

};

#endif
