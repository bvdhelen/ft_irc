#include "commands/UserCommand.hpp"

UserCommand::UserCommand(std::vector<std::string> params)
{
	_params = params;
}

UserCommand::~UserCommand()
{ }

void UserCommand::execute(Server &server, Client &client)
{
	if (client.isAuthenticated())
	{
		server.sendReplyToClient(&client, ERR_ALREADYREGISTERED, "You may not re-register");
		return ;
	}
	else if (_params.size() < 4)
	{
		server.sendReplyToClient(&client, ERR_NEEDMOREPARAMS, "Not enough parameters", "USER");
		return ;
	}
	client.setUsername(_params[0]);
	client.setHasUser(true);
	client.setRealname(_params[3]);
	if (client.getHasUser() && client.getHasNick())
	{
		if (client.getPassOk())
		{
			server.sendReplyToClient(&client, RPL_WELCOME, "Welcome to the IRC Network");
			client.setAuthenticated(true);
		}
		else
		{
			server.sendReplyToClient(&client, ERR_PASSWDMISMATCH, "Password incorrect");
			client.setRequestedDisconnection(true);
		}
	}
}
