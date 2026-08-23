#include "commands/ModeCommand.hpp"
#include "Channel.hpp"
#include "Replies.hpp"

ModeCommand::ModeCommand(const std::vector<std::string> &params)
{
	_params = params;
}

ModeCommand::~ModeCommand() {}

void ModeCommand::execute(Server &server, Client &client)
{
	if (_params.size() < 2)
		return server.sendReplyToClient(&client, ERR_NEEDMOREPARAMS, "Not enough parameters", "MODE");

	Channel *channel = server.getChannelByName(_params[0]);
	if (!channel)
		return server.sendReplyToClient(&client, ERR_NOSUCHCHANNEL, "No such channel", _params[0]);

	if (!channel->hasClient(&client))
		return server.sendReplyToClient(&client, ERR_NOTONCHANNEL, "You're not on that channel", _params[0]);

	if (!channel->isOperator(&client))
		return server.sendReplyToClient(&client, ERR_CHANOPRIVSNEEDED, "You're not channel operator", _params[0]);
}
