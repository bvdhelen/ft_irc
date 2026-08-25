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

	applyModes(channel, client, server, _params[1]);
}

void ModeCommand::applyModes(Channel *channel, Client &client, Server &server, const std::string &modestring)
{
	bool adding = true;
	size_t paramIndex = 2;
	std::string appliedModes;
	std::string appliedParams;

	for (size_t i = 0; i < modestring.size(); i++)
	{
		char c = modestring[i];
		if (c == '+') { adding = true; continue; }
		if (c == '-') { adding = false; continue; }
		bool hasAppliedParams = false;

		switch (c)
		{
			case 'i': // invite only
				if (channel->isInviteOnly() != adding)
				{
					channel->setInviteOnly(adding);
					appliedModes += (adding ? "+i" : "-i");
				}
				break;
			case 't': // topic is protected
				if (channel->isProtectedTopic() != adding)
				{
					channel->setProtectedTopic(adding);
					appliedModes += (adding ? "+t" : "-t");
				}
				break;
			case 'k': // key (password)
				if (adding)
				{
					if (paramIndex < _params.size())
					{
						channel->setPassword(_params[paramIndex]);
						appliedModes += "+k";
						hasAppliedParams = true;
					}
				}
				else if (channel->hasPassword())
				{
					channel->removePassword();
					appliedModes += "-k";
				}
				break;
			case 'l': // user limit
				if (adding)
				{
					if (paramIndex < _params.size())
					{
						channel->setUserLimit(std::atoi(_params[paramIndex].c_str()));
						appliedModes += "+l";
						hasAppliedParams = true;
					}
				}
				else if (channel->hasUserLimit())
				{
					channel->removeUserLimit();
					appliedModes += "-l";
				}
				break;
			case 'o': // make/quit operator
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

						appliedModes += (adding ? "+o" : "-o");
						hasAppliedParams = true;
					}
				}
				break;
			}
			default:
			{
				server.sendReplyToClient(&client, ERR_UNKNOWNMODE, ":is an unknown mode char to me", std::string(&c));
				break;
			}

			if (hasAppliedParams)
			{
				// ! TODO FIX no aparecen los parametros en las respuestas
				appliedParams += " " + _params[paramIndex];
				paramIndex++;
			}
		}
	}

	if (!appliedModes.empty())
	{
		std::string msg = ":" + client.getNickname() + "!" + client.getUsername() + "@" + client.getHost()
			+ " MODE " + channel->getName() + " " + appliedModes + appliedParams + "\r\n";
		server.sendToChannelRaw(channel, msg);
	}
}
