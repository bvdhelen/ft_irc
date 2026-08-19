#ifndef PRIVMSGCOMMAND_HPP
# define PRIVMSGCOMMAND_HPP

#include "Replies.hpp"
#include "Command.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

class PrivmsgCommand : public Command
{
    public:
        PrivmsgCommand(const std::vector<std::string> &params);
        ~PrivmsgCommand();

        void execute(Server &server, Client &client);
};

#endif
