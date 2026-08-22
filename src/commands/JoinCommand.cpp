#include "JoinCommand.hpp"

JoinCommand::JoinCommand(const std::vector<std::string> &params)
{
    _params = params;
}

JoinCommand::~JoinCommand()
{
}

void JoinCommand::execute(Server &server, Client &client)
{
    std::string channelName;
    Channel *channel;

    if (_params.empty())
    {
        server.sendReplyToClient(
            client.getSocket(),
            ERR_NEEDMOREPARAMS,
            "Not enough parameters");
        return ;
    }
    channelName = _params[0];
    channel = server.getChannelByName(channelName);
    if (channel == NULL)
    {
        //TODO: El servidor tendrá que crear el canal.
        //server.createAndJoinNewChannel(client, channelName);
        return ;
    }
    if (client.isInChannel(channel))
        return ;
    if (channel->isInviteOnly())
    {
        if (!channel->isInvited(client))
        {
            server.sendReplyToClient(
                client,
                ERR_INVITEONLYCHAN,
                channelName + " :Cannot join channel (+i)");
            return ;
        }
        channel->removeInvited(client);
    }
    if (channel->hasPassword())
    {
        if (_params.size() < 2)
        {
            // ERR_BADCHANNELKEY
            return ;
        }
        if (!channel->checkPassword(_params[1]))
        {
            // ERR_BADCHANNELKEY
            return ;
        }
    }
    if (channel->isFull())
    {
        // ERR_CHANNELISFULL
        return ;
    }
    client.addChannel(channel);
    // Aquí enviaremos JOIN
    // Aquí enviaremos TOPIC
    // Aquí enviaremos NAMES
}
