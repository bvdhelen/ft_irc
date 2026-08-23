#include "commands/ModeCommand.hpp"
#include "Channel.hpp"

ModeCommand::ModeCommand(const std::vector<std::string> &params)
{
	_params = params;
}

ModeCommand::~ModeCommand() {}

void ModeCommand::execute(Server &server, Client &client)
{
}
