#include "KickCommand.hpp"

KickCommand::KickCommand(const std::vector<std::string> &params)
{
	_params = params;
}

KickCommand::~KickCommand(void)
{
}

void KickCommand::kickClient(Server &server, Client &client, const std::string &channelName, const std::string &nickname)
{
	Channel *channel;
	Client *target;
	std::string message;

	channel = server.getChannelByName(channelName);
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
	if (!channel->isOperator(&client))
	{
		server.sendReplyToClient(
			client.getSocket(),
			ERR_CHANOPRIVSNEEDED,
			"You're not channel operator");
		return ;
	}
	target = server.getClientByNick(nickname);
	if (target == NULL)
	{
		server.sendReplyToClient(
			client.getSocket(),
			ERR_NOSUCHNICK,
			"No such nick");
		return ;
	}
	if (!target->isInChannel(channel))
	{
		server.sendReplyToClient(
			client.getSocket(),
			ERR_USERNOTINCHANNEL,
			"They are not on that channel");
		return ;
	}
	message = ":" + client.getNickname() + "!"
		+ client.getUsername() + " KICK "
		+ channel->getName() + " "
		+ target->getNickname();
    if (_params.size() > 2)
        message += " :" + _params[2];
    message += "\r\n";
	server.sendToChannel(channel, message);
	target->removeChannel(channel);
    if (channel->isEmpty())
        server.removeChannel(channel->getName());
}

void KickCommand::execute(Server &server, Client &client)
{
    if (_params.size() < 2)
	{
		server.sendReplyToClient(
			client.getSocket(),
			ERR_NEEDMOREPARAMS,
			"Not enough parameters");
		return ;
	}
	kickClient(server, client, _params[0], _params[1]);
}
