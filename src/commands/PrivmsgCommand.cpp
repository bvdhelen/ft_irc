#include "PrivmsgCommand.hpp"

PrivmsgCommand::PrivmsgCommand(const std::vector<std::string> &params)
{
    _params = params;
}

PrivmsgCommand::~PrivmsgCommand()
{
}

void PrivmsgCommand::execute(Server &server, Client &client)
{

}
