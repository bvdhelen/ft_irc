#include "commands/JoinCommand.hpp"

JoinCommand::JoinCommand(const std::vector<std::string> &params)
{
    _params = params;
}

JoinCommand::~JoinCommand()
{
}

void JoinCommand::execute(Server &server, Client &client)
{
    std::string channelName;
    std::vector<std::string> channels;
    std::vector<std::string> passwd;
    Channel *channel;

    if (_params.empty())
    {
        server.sendReplyToClient(
            &client,
            ERR_NEEDMOREPARAMS,
            "Not enough parameters",
            "JOIN");
        return ;
    }
    channels = splitStrings(_params[0]);
    if (_params.size() >= 2)
        passwd = splitStrings(_params[1]);
    for (size_t i = 0; i < channels.size(); i++)
    {
        channelName = channels[i];
        if (channelName[0] != '#')
        {
            server.sendReplyToClient(&client, ERR_NOSUCHCHANNEL, "No such channel", channelName);
            continue;
        }
        channel = server.getChannelByName(channelName);
        //Ask for real channelName to match specific capital letters.
        if (channel != NULL)
            channelName = channel->getName();
        std::string password = "";
        if (i < passwd.size())
            password = passwd[i];
        handleJoinChannel(server, client, channel, channelName, password);
    }
}

std::vector<std::string> JoinCommand::splitStrings(const std::string &channels)
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

void JoinCommand::handleJoinChannel(Server &server, Client &client, Channel *channel, const std::string& channelName, const std::string &password)
{
    if (channel == NULL)
    {
        channel = server.createChannel(channelName, password);
        if (channel == NULL)
            return ;
        client.addChannel(channel);
        channel->addOperator(&client);
    }
    else
    {
        if (client.isInChannel(channel))
            return ;
        if (channel->isInviteOnly())
        {
            if (!channel->isInvited(&client))
            {
                server.sendReplyToClient(
                    &client,
                    ERR_INVITEONLYCHAN,
                    channelName + " :Cannot join channel (+i)");
                return ;
            }
            channel->removeInvited(&client);
        }
        if (channel->hasPassword() && (_params.size() < 2 || !channel->checkPassword(_params[1])))
        {
            server.sendReplyToClient(
                &client,
                ERR_BADCHANNELKEY,
                channelName + " :Cannot join channel (+k)");
            return ;
        }
        if (channel->isFull())
        {
            server.sendReplyToClient(
                &client,
                ERR_CHANNELISFULL,
                channelName + " :Cannot join channel (+l)");
            return ;
        }
        client.addChannel(channel);
    }
    
    // Send JOIN
    std::string joinMsg = ":" + client.getNickname() + "!" + client.getUsername() +
                        "@" + client.getHost() + " JOIN " + channelName + "\r\n";
    server.sendToChannelRaw(channel, joinMsg);

    // Send TOPIC
    if (!channel->getTopic().empty())
        server.sendReplyToClient(&client, RPL_TOPIC,
                                channelName + " :" + channel->getTopic());
    else
        server.sendReplyToClient(&client, RPL_NOTOPIC,
                                channelName + " :No topic is set");

    // Send NAMES
    std::string namesList;
    const std::set<Client*>& clients = channel->getClients();
    for (std::set<Client*>::const_iterator it = clients.begin(); it != clients.end(); ++it)
    {
        if (it != clients.begin())
            namesList += " ";
        if (channel->isOperator(*it))
            namesList += "@";
        namesList += (*it)->getNickname();
    }
    server.sendReplyToClient(&client, RPL_NAMREPLY, "= " + channelName + " :" + namesList);
    server.sendReplyToClient(&client, RPL_ENDOFNAMES, channelName + " :End of NAMES list");
}
