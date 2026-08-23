#include "parser/CommandFactory.hpp"

Command *CommandFactory::createCommand(const std::string &commandName, const std::vector<std::string> &params)
{
	(void)commandName, (void)params; // TODO delete this line when 1st command is implemented
	// TODO: add/uncomment commands as they are implemented
	// if (commandName == "JOIN")		return new JoinCommand(params);
	// if (commandName == "NICK")		return new NickCommand(params);
	// if (commandName == "USER")		return new UserCommand(params);
	// if (commandName == "PASS")		return new PassCommand(params);
	// if (commandName == "PRIVMSG")	return new PrivmsgCommand(params);
	// if (commandName == "PART")		return new PartCommand(params);
	// if (commandName == "QUIT")		return new QuitCommand(params);
	// if (commandName == "KICK")		return new KickCommand(params);
	// if (commandName == "INVITE")		return new InviteCommand(params);
	// if (commandName == "TOPIC")		return new TopicCommand(params);
	// if (commandName == "MODE")		return new ModeCommand(params);
	
	return NULL; // default if no command is found
}
