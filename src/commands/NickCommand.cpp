#include "commands/NickCommand.hpp"

NickCommand::NickCommand(const std::vector<std::string>& params)
{
	_params = params;
}

NickCommand::~NickCommand()
{ }

void NickCommand::notifyClients(Server& server, Client& client, std::string oldNickname, std::string newNickname)
{
	std::set<Client *> notified;
	const std::set<Channel *> &channels = client.getChannels();
	const std::string message = ":" + oldNickname + " NICK :" + newNickname + "\r\n";

	notified.insert(&client);
	for (std::set<Channel *>::const_iterator it = channels.begin(); it != channels.end(); it++)
	{
		const std::set<Client *> &members = (*it)->getClients();
		for (std::set<Client *>::const_iterator mit = members.begin(); mit != members.end(); mit++)
			notified.insert(*mit);
	}

	for (std::set<Client *>::const_iterator nit = notified.begin(); nit != notified.end(); nit++)
		server.sendReplyToClientRaw(*nit, message);
}

//   nickname = ( letter / special ) *8( letter / digit / special / "-" )
//   special  = "[", "]", "\", "`", "_", "^", "{", "|", "}"
bool NickCommand::isValidNickname(const std::string &nickname)
{
	if (nickname.empty())
		return false;

	for (size_t i = 0; i < nickname.length(); i++)
	{
		char c = nickname[i];
		bool isSpecial = (c == '[' || c == ']' || c == '\\' || c == '`'
				|| c == '_' || c == '^' || c == '{' || c == '|' || c == '}');

		if (i == 0 && !std::isalpha(c) && !isSpecial)
			return false;
		else if (!std::isalnum(c) && !isSpecial && c != '-')
			return false;
	}
	return true;
}

bool NickCommand::isNicknameInUse(Server &server, const std::string nickname)
{
	std::list<Client *> clients = server.getAllClients();
	std::list<Client *>::iterator it = clients.begin();
	for (; it != clients.end(); it++)
	{
		if ((*it)->getNickname().compare(nickname) == 0)
			return true;
	}
	return false;
}

void NickCommand::execute(Server &server, Client &client)
{
	if (_params.empty())
	{
		server.sendReplyToClient(&client, ERR_NONICKNAMEGIVEN, "No nickname given.");
		return;
	}
	else if (client.getHasNick() && client.getNickname() .compare(_params[0]) == 0)
		return;
	
	std::string nick = _params[0].substr(0, 9);
	if (!isValidNickname(nick))
		server.sendReplyToClient(&client, ERR_ERRONEUSNICKNAME, "Erroneous nickname", nick);
	else if (isNicknameInUse(server, nick))
		server.sendReplyToClient(&client, ERR_NICKNAMEINUSE, "Nickname is already in use", nick);
	else if (client.isAuthenticated())
	{
		std::string oldNick = client.getNickname();
		notifyClients(server, client, oldNick, nick);
		client.setNickname(nick);
	}
	else
	{
		client.setNickname(nick);
		client.setHasNick(true);
		if (client.getHasUser())
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
}
