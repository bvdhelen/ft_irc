#include "commands/TopicCommand.hpp"

TopicCommand::TopicCommand(const std::vector<std::string> &params)
{
	_params = params;
}

TopicCommand::~TopicCommand(void)
{
}

void TopicCommand::execute(Server &server, Client &client)
{
	Channel *channel;

	if (_params.empty())
	{
		server.sendReplyToClient(
			&client,
			ERR_NEEDMOREPARAMS,
			"Not enough parameters",
			"TOPIC");
		return ;
	}
	if (_params.size() > 2)
		return ;
	channel = server.getChannelByName(_params[0]);
	if (channel == NULL)
	{
		server.sendReplyToClient(
			&client,
			ERR_NOSUCHCHANNEL,
			"No such channel");
		return ;
	}
	if (!channel->hasClient(&client))
	{
		server.sendReplyToClient(
			&client,
			ERR_NOTONCHANNEL,
			"You're not on that channel");
		return ;
	}
	if (_params.size() == 1)
	{
		sendCurrentTopic(server, client, channel);
		return ;
	}
	setTopic(server, client, channel, _params[1]);
}

void TopicCommand::sendCurrentTopic(Server &server, Client &client, Channel *channel)
{
	if (channel->getTopic().empty())
	{
		server.sendReplyToClient(
			&client,
			RPL_NOTOPIC,
			"No topic is set");
		return ;
	}
	server.sendReplyToClient(
		&client,
		RPL_TOPIC,
		channel->getTopic(),
		channel->getName());
}

void TopicCommand::setTopic(Server &server, Client &client, Channel *channel, const std::string &topic)
{
	std::string message;

	if (channel->isProtectedTopic()
		&& !channel->isOperator(&client))
	{
		server.sendReplyToClient(
			&client,
			ERR_CHANOPRIVSNEEDED,
			"You're not channel operator");
		return ;
	}
	channel->setTopic(topic);
	message = ":" + client.getNickname() + "!"
		+ client.getUsername() + "@"
    	+ client.getHost() + " TOPIC "
		+ channel->getName() + " :" + topic + "\r\n";
	server.sendToChannelRaw(channel, message);
}
