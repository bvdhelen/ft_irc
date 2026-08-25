#include "parser/CommandFactory.hpp"
#include "commands/PingCommand.hpp"
#include "commands/PartCommand.hpp"
#include "commands/QuitCommand.hpp"
# include "commands/KickCommand.hpp"
# include "commands/TopicCommand.hpp"
# include "commands/PrivmsgCommand.hpp"

static void toUpper(std::string &s);

Command *CommandFactory::createCommand(std::string commandName, const std::vector<std::string> &params)
{
	toUpper(commandName);

	// TODO: add/uncomment commands as they are implemented
	// if (commandName == "JOIN")		return new JoinCommand(params);
	// if (commandName == "NICK")		return new NickCommand(params);
	// if (commandName == "USER")		return new UserCommand(params);
	// if (commandName == "PASS")		return new PassCommand(params);
	if (commandName == "PRIVMSG")		return new PrivmsgCommand(params);
	if (commandName == "PART")			return new PartCommand(params);
	if (commandName == "QUIT")			return new QuitCommand(params);
	if (commandName == "KICK")			return new KickCommand(params);
	if (commandName == "TOPIC")			return new TopicCommand(params);
	// if (commandName == "INVITE")		return new InviteCommand(params);
	// if (commandName == "MODE")		return new ModeCommand(params);
	if (commandName == "PING")		return new PingCommand(params);
	
	return NULL; // default if no command is found
}

static void toUpper(std::string &s)
{
	for (size_t i = 0; i < s.length(); i++)
        s[i] = toupper(s[i]);
}
