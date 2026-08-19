#include "Command.hpp"

Command::Command()
{
}

Command::~Command()
{
}

const std::vector<std::string> &Command::getParams() const
{
    return _params;
}
