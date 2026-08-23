#include "commands/PassCommand.hpp"

PassCommand::PassCommand(std::vector<std::string> params)
{
	_params = params;
}

PassCommand::~PassCommand()
{ }

void PassCommand::execute(Server &server, Client &client)
{
	if (client.isAuthenticated())
		server.sendReplyToClient(&client, ERR_ALREADYREGISTERED, "You may not re-register");
	else if (_params.empty())
		server.sendReplyToClient(&client, ERR_NEEDMOREPARAMS, "Not enough parameters", "PASS");
	else if (server.getPassword().compare(_params[0]) != 0)
		client.setPassOk(false);
	else
		client.setPassOk(true);
}
