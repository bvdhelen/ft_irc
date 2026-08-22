#include "InviteCommand.hpp"

InviteCommand::InviteCommand(const std::vector<std::string> &params)
{
	_params = params;
}

InviteCommand::~InviteCommand(void)
{
}

void InviteCommand::execute(Server &server, Client &client)
{
    Channel *channel;
    Client *target;
    std::string message;

    if (_params.size() != 2)
    {
        server.sendReplyToClient(
            client.getSocket(),
            ERR_NEEDMOREPARAMS,
            "Not enough parameters");
        return ;
    }
    target = server.getClientByNick(_params[0]);
    if (target == NULL)
    {
        server.sendReplyToClient(
            client.getSocket(),
            ERR_NOSUCHNICK,
            "No such nick");
        return ;
    }
    channel = server.getChannelByName(_params[1]);
    if (channel == NULL)
    {
        server.sendReplyToClient(
            client.getSocket(),
            ERR_NOSUCHCHANNEL,
            "No such channel");
        return ;
    }
    if (!client.isInChannel(channel))
    {
        server.sendReplyToClient(
            client.getSocket(),
            ERR_NOTONCHANNEL,
            "You're not on that channel");
        return ;
    }
    if (channel->isInviteOnly() && !channel->isOperator(&client))
    {
        server.sendReplyToClient(
            client.getSocket(),
            ERR_CHANOPRIVSNEEDED,
            "You're not channel operator");
        return ;
    }
    if (target->isInChannel(channel))
    {
        server.sendReplyToClient(
            client.getSocket(),
            ERR_USERONCHANNEL,
            "User is already on channel");
        return ;
    }
    message = ":" + client.getNickname() + "!"
        + client.getUsername() + " INVITE "
        + target->getNickname() + " "
        + channel->getName() + "\r\n";
    server.sendToClient(target, message);
}
