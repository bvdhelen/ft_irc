#include "commands/PrivmsgCommand.hpp"

PrivmsgCommand::PrivmsgCommand(const std::vector<std::string> &params)
{
    _params = params;
}

PrivmsgCommand::~PrivmsgCommand()
{
}

void PrivmsgCommand::execute(Server &server, Client &client)
{
    std::string message;
    Client *targetClient;
    Channel *channel;

    if (_params.size() < 2)
    {
        server.sendReplyToClient(
            &client,
            ERR_NEEDMOREPARAMS,
            "Not enough parameters",
            "PRIVMSG");
        return ;
    }
    message = ":" + client.getNickname() + "!"
        + client.getUsername() + "@"
        + client.getHost() + " PRIVMSG "
        + _params[0] + " :"
        + _params[1] + "\r\n";
    if (_params[0][0] == '#')
    {
        channel = server.getChannelByName(_params[0]);
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
                ERR_CANNOTSENDTOCHAN,
                "Cannot send to channel");
            return ;
        }
        server.sendToChannelExceptRaw(channel, &client, message);
    }
    else
    {
        targetClient = server.getClientByNick(_params[0]);
        if (targetClient == NULL)
        {
            server.sendReplyToClient(
                &client,
                ERR_NOSUCHNICK,
                "No such nick");
            return ;
        }
        server.sendReplyToClientRaw(targetClient, message);
    }
}
