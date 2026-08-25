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
    if (!_params.empty())
        client.setQuitMessage(_params[0]);
    client.setRequestedDisconnection(true);
    (void)server;
}
