#include "PartCommand.hpp"

PartCommand::PartCommand(const std::vector<std::string> &params)
{
    _params = params;
}

PartCommand::~PartCommand()
{
}

void PartCommand::execute(Server &server, Client &client)
{
    Channel *channel;

    if (_params.empty())
    {
        // ERR_NEEDMOREPARAMS
        return ;
    }
    channel = server.getChannelByName(_params[0]);
    if (channel == NULL)
    {
        // ERR_NOSUCHCHANNEL
        return ;
    }
    if (!client.isInChannel(channel))
    {
        // ERR_NOTONCHANNEL
        return ;
    }
    // Enviar el PART
    client.removeChannel(channel);
}
