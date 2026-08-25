#include "commands/ModeCommand.hpp"
#include "Channel.hpp"
#include "Replies.hpp"
#include <cstdlib>

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

	applyModes(channel, client, server, _params[1]);
}

void ModeCommand::applyModes(Channel *channel, Client &client, Server &server, const std::string &modestring)
{
	bool adding = true;
	size_t paramIndex = 2;

	for (size_t i = 0; i < modestring.size(); i++)
	{
		char c = modestring[i];
		if (c == '+') { adding = true; continue; }
		if (c == '-') { adding = false; continue; }

		switch (c)
		{
			case 'i':
				channel->setInviteOnly(adding);
				break;
			case 't':
				channel->setProtectedTopic(adding);
				break;
			case 'k':
				if (adding && paramIndex < _params.size())
				{
					channel->setPassword(_params[paramIndex]);
					paramIndex++;
				}
				else
					channel->removePassword();
				break;
			case 'l':
				if (adding && paramIndex < _params.size())
				{
					channel->setUserLimit(std::atoi(_params[paramIndex].c_str()));
					paramIndex++;
				}
				else
					channel->removeUserLimit();
				break;
			case 'o':
			{
				if (paramIndex < _params.size())
				{
					Client *target = server.getClientByNick(_params[paramIndex]);
					if (target && channel->hasClient(target))
					{
						if (adding)
							channel->addOperator(target);
						else
							channel->removeOperator(target);
					}
					paramIndex++;
				}
				break;
			}
			default:
			{
				server.sendReplyToClient(&client, ERR_UNKNOWNMODE, ":is unknown mode char to me " + channel->getName(), std::string(&c));
				break;
			}
		}
	}
}
