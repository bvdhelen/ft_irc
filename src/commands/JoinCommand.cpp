#include "commands/JoinCommand.hpp"

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
            &client,
            ERR_NEEDMOREPARAMS,
            "Not enough parameters",
            "JOIN");
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
        if (!channel->isInvited(&client))
        {
            server.sendReplyToClient(
                &client,
                ERR_INVITEONLYCHAN,
                channelName + " :Cannot join channel (+i)");
            return ;
        }
        channel->removeInvited(&client);
    }
    if (channel->hasPassword())
    {
        if (_params.size() < 2)
        {
            server.sendReplyToClient(
                &client,
                ERR_BADCHANNELKEY,
                channelName + " :Cannot join channel (+k)");
            return ;
        }
        if (!channel->checkPassword(_params[1]))
        {
            server.sendReplyToClient(
                &client,
                ERR_BADCHANNELKEY,
                channelName + " :Cannot join channel (+k)");
            return ;
        }
    }
    if (channel->isFull())
    {
        server.sendReplyToClient(
            &client,
            ERR_CHANNELISFULL,
            channelName + " :Cannot join channel (+l)");
        return ;
    }
    client.addChannel(channel);
    
    // Enviar JOIN, TOPIC, NAMES (igual que en la creación)
    std::string joinMsg = ":" + client.getNickname() + "!" + client.getUsername() +
                          "@" + client.getHost() + " JOIN " + channelName;
    server.sendToChannelRaw(channel, joinMsg);

    if (!channel->getTopic().empty())
        server.sendReplyToClient(&client, RPL_TOPIC,
                                 channelName + " :" + channel->getTopic());
    else
        server.sendReplyToClient(&client, RPL_NOTOPIC,
                                 channelName + " :No topic is set");

    // Enviar NAMES (igual que en createAndJoinNewChannel)
    std::string namesList;
    const std::set<Client*>& clients = channel->getClients();
    for (std::set<Client*>::const_iterator it = clients.begin(); it != clients.end(); ++it)
    {
        if (it != clients.begin())
            namesList += " ";
        if (channel->isOperator(*it))
            namesList += "@";
        namesList += (*it)->getNickname();
    }
    server.sendReplyToClient(&client, RPL_NAMREPLY, "= " + channelName + " :" + namesList);
    server.sendReplyToClient(&client, RPL_ENDOFNAMES, channelName + " :End of NAMES list");
}
