#ifndef PARTCOMMAND_HPP
# define PARTCOMMAND_HPP

#include "Replies.hpp"
#include "Command.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

class PartCommand : public Command
{
    private:
        std::vector<std::string> splitChannels(const std::string &channels);
        void partChannel(Server &server, Client &client, const std::string &channelName);
    public:
        PartCommand(const std::vector<std::string> &params);
        ~PartCommand();

        void execute(Server &server, Client &client);
};

#endif
