#include "parser/CommandParser.hpp"
#include "commands/Command.hpp"
#include "parser/CommandFactory.hpp"
#include "Replies.hpp"

void CommandParser::parseAndExecute(std::string line, Server &server, Client &client)
{
	std::string commandName = parseCommandName(line);

	std::vector<std::string> params;
	parseParams(line, params);

	Command *cmd = CommandFactory::createCommand(commandName, params);
	if (!cmd)
		return server.sendReplyToClient(&client, ERR_UNKNOWNCOMMAND, "Unknown command", commandName);
	
	cmd->execute(server, client);

	delete cmd;
}

std::string CommandParser::parseCommandName(std::string &line)
{
	std::string::size_type space = line.find(' ');
	std::string command = line.substr(0, space);

	if (space == std::string::npos)
		line.clear();
	else
		line = line.substr(space + 1);
	return command;
}

void CommandParser::parseParams(std::string &line, std::vector<std::string> &params)
{
	while (!line.empty())
	{
		// msg after : is read as 1 param and is always the last one
		if (line[0] == ':')
		{
			params.push_back(line.substr(1));
			return;
		}

		std::string::size_type space = line.find(' ');
		params.push_back(line.substr(0, space));

		// is the last param
		if (space == std::string::npos)
			return;

		line = line.substr(space + 1);
	}
}
