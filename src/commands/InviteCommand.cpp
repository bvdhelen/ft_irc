#include "commands/InviteCommand.hpp"

InviteCommand::InviteCommand(const std::vector<std::string> &params)
{
	_params = params;
}

InviteCommand::~InviteCommand(void)
{
}

void InviteCommand::execute(Server &server, Client &client)
{
    Client *target;
    Channel *channel;
    std::string message;

    if (_params.size() != 2)
    {
        server.sendReplyToClient(
            &client,
            ERR_NEEDMOREPARAMS,
            "Not enough parameters");
        return ;
    }
    target = server.getClientByNick(_params[0]);
    if (target == NULL)
    {
        server.sendReplyToClient(
            &client,
            ERR_NOSUCHNICK,
            "No such nick");
        return ;
    }
    channel = server.getChannelByName(_params[1]);
    if (channel == NULL)
    {
        server.sendReplyToClient(
            &client,
            ERR_NOSUCHCHANNEL,
            "No such channel");
        return ;
    }
    if (!client.isInChannel(channel))
    {
        server.sendReplyToClient(
            &client,
            ERR_NOTONCHANNEL,
            "You're not on that channel");
        return ;
    }
    if (channel->isInviteOnly() && !channel->isOperator(&client))
    {
        server.sendReplyToClient(
            &client,
            ERR_CHANOPRIVSNEEDED,
            "You're not channel operator");
        return ;
    }
    if (target->isInChannel(channel))
    {
        server.sendReplyToClient(
            &client,
            ERR_USERONCHANNEL,
            "User is already on channel");
        return ;
    }
    channel->addInvited(target);
    message = ":" + client.getNickname() + "!"
        + client.getUsername() + "@"
        + client.getHost() + " INVITE "
        + target->getNickname() + " "
        + channel->getName() + "\r\n";
    server.sendReplyToClientRaw(target, message);
    message = ":ft_irc 341 " + client.getNickname() + " "
    + target->getNickname() + " "
    + channel->getName() + "\r\n";

server.sendReplyToClientRaw(&client, message);
}
