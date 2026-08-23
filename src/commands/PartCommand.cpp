#include "commands/PartCommand.hpp"

PartCommand::PartCommand(const std::vector<std::string> &params)
{
    _params = params;
}

PartCommand::~PartCommand()
{
}

std::vector<std::string> PartCommand::splitChannels(const std::string &channels)
{
    std::string::size_type start;
    std::string::size_type comma;
    std::string channel;
    std::vector<std::string> result;

    if (channels.empty() || channels[0] == ',' || channels[channels.size() - 1] == ',')
        return result;
    start = 0;
    while (start < channels.size())
    {
        comma = channels.find(',', start);
        if (comma == start)
            return std::vector<std::string>();
        if (comma == std::string::npos)
        {
            channel = channels.substr(start);
            result.push_back(channel);
            break ;
        }
        channel = channels.substr(start, comma - start);
        result.push_back(channel);
        start = comma + 1;
    }
    return result;
}

void PartCommand::partChannel(Server &server, Client &client, const std::string &channelName)
{
    Channel *channel;
    std::string message;

    channel = server.getChannelByName(channelName);
    if (channel == NULL)
    {
        server.sendReplyToClient(
            &client,
            ERR_NOSUCHCHANNEL,
            "No such channel");
    }
    else if (!client.isInChannel(channel))
    {
        server.sendReplyToClient(
            &client,
            ERR_NOTONCHANNEL,
            "You're not on that channel");
    }
    else
    {
        message = ":" + client.getNickname() + "!"
        + client.getUsername() + "@"
        + client.getHost() + " PART "
        + channelName;
        if (_params.size() > 1)
            message += " :" + _params[1];
        message += "\r\n";
        server.sendToChannelRaw(channel, message);
        client.removeChannel(channel);
        if (channel->isEmpty())
            server.removeChannel(channel->getName());
    }
}

void PartCommand::execute(Server &server, Client &client)
{
    std::vector<std::string> channels;
    std::vector<std::string>::iterator it;

    if (_params.empty())
    {
        server.sendReplyToClient(
            &client,
            ERR_NEEDMOREPARAMS,
            "Not enough parameters");
        return ;
    }
    channels = splitChannels(_params[0]);
    if (channels.empty())
    {
        server.sendReplyToClient(
            &client,
            ERR_NOSUCHCHANNEL,
            "No such channel");
        return ;
    }
    it = channels.begin();
    while (it != channels.end())
    {
        partChannel(server, client, *it);
        ++it;
    }
}
