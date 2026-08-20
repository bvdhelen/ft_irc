#include "QuitCommand.hpp"

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
        + client.getUsername() + " QUIT\r\n";
    if (!_params.empty())
        message += " " + _params[0];
    message += "\r\n";
    it = client.getChannels().begin();
    while (it != client.getChannels().end())
    {
        server.sendToChannelExcept(*it, &client, message);
        ++it;
    }
    client.disconnect();
    server.removeEmptyChannels();
    client.setRequestedDisconnection(true);
}
