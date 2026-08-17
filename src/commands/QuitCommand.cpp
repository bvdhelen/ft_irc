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
    (void)server;
    client.disconnect();
}
