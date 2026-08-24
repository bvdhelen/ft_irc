#include "commands/PingCommand.hpp"

PingCommand::PingCommand(const std::vector<std::string>& params)
{
	_params = params;
}

PingCommand::~PingCommand() {}

void PingCommand::execute(Server& server, Client &client)
{
	if (_params.empty())
	{
		server.sendReplyToClient(&client, ERR_NEEDMOREPARAMS, "Not enough parameters", "PING");
		return;
	}
	server.sendReplyToClientRaw(&client, ":ft_irc PONG ft_irc :" + _params[0] + "\r\n");
}
