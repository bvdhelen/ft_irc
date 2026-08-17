#ifndef PARTCOMMAND_HPP
# define PARTCOMMAND_HPP

#include "Command.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

class PartCommand : public Command
{
    public:
        PartCommand(const std::vector<std::string> &params);
        ~PartCommand();

        void execute(Server &server, Client &client);
};

#endif
