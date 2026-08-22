#include "CommandParser.hpp"

void CommandParser::parseAndExecute(std::string line, Server &server, Client &client)
{
	std::string command = parseCommand(line);

	if (command.empty())
		return;

	std::vector<std::string> params;
	parseParams(line, params);

	// TODO: create command via CommandFactory and execute
	// TODO: try-catch para excepciones de comandos
	(void)server;
	(void)client;
	(void)command;
	(void)params;
}

std::string CommandParser::parseCommand(std::string &line)
{
	std::string command;
	std::string::size_type space = line.find(' ');

	if (space == std::string::npos)
	{
		command = line;
		line.clear();
		return command;
	}

	command = line.substr(0, space);
	line = line.substr(space + 1);
	return command;
}

void CommandParser::parseParams(std::string line, std::vector<std::string> &params)
{
	while (true)
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
