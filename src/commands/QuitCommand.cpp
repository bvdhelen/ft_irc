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
    it = client.getChannels().begin();
    while (it != client.getChannels().end())
    {
        server.sendToChannelExcept(*it, &client, message);
        ++it;
    }
    client.disconnect();
    //TODO: gestionar la desconexion
    //los canales que se han quedado vacios siguen estando en Server::_channels
    //TENEMOS QUE DECIDIR DONDE ELIMINAR LOS CANALES VACIOS
}
