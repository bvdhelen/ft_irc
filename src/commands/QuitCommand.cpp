#include "commands/QuitCommand.hpp"

QuitCommand::QuitCommand(const std::vector<std::string> &params)
{
    _params = params;
}

QuitCommand::~QuitCommand()
{
}

void QuitCommand::execute(Server &server, Client &client)
{
    std::string message;
    std::set<Channel *>::const_iterator it;

    message = ":" + client.getNickname() + "!"
        + client.getUsername() + "@"
        + client.getHost() + " QUIT";
    if (!_params.empty())
        message += " :" + _params[0];
    message += "\r\n";
    it = client.getChannels().begin();
    while (it != client.getChannels().end())
    {
        server.sendToChannelExceptRaw(*it, &client, message);
        ++it;
    }
    client.setRequestedDisconnection(true);
}
