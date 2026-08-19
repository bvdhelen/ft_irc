#include "PartCommand.hpp"

PartCommand::PartCommand(const std::vector<std::string> &params)
{
    _params = params;
}

PartCommand::~PartCommand()
{
}

//TODO: TIENE QUE PERMITIR VARIOS CANALES EN UN PART??
// PART #canal1,#canal2
void PartCommand::execute(Server &server, Client &client)
{
    Channel *channel;
    std::string message;
    std::set<Client *>::const_iterator it;

    if (_params.empty())
    {
        server.sendReplyToClient(
            client.getSocket(),
            ERR_NEEDMOREPARAMS,
            "Not enough parameters");
        return ;
    }
    channel = server.getChannelByName(_params[0]);
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
    message = ":" + client.getNickname() + "!"
        + client.getUsername() + " PART "
        + _params[0] + "\r\n";
    it = channel->getClients().begin();
    while (it != channel->getClients().end())
    {
        send((*it)->getSocket(), message.c_str(), message.size(), 0);
        ++it;
    }
    client.removeChannel(channel);
}
