#include "Client.hpp"

// Constructor
Client::Client(int socket)
    : _socket(socket),
      _nickname(""),
      _username(""),
      _realname(""),
      _buffer(""),
      _passOk(false),
      _hasNick(false),
      _hasUser(false),
      _authenticated(false)
{
}

// Destructor
Client::~Client()
{
}

int Client::getSocket() const
{
    return _socket;
}

const std::string &Client::getNickname() const
{
    return _nickname;
}

const std::string &Client::getUsername() const
{
    return _username;
}

const std::string &Client::getRealname() const
{
    return _realname;
}

const std::string &Client::getBuffer() const
{
    return _buffer;
}

bool Client::getPassOk() const
{
    return _passOk;
}

bool Client::getHasNick() const
{
    return _hasNick;
}

bool Client::getHasUser() const
{
    return _hasUser;
}

bool Client::isAuthenticated() const
{
    return _authenticated;
}

const std::set<Channel *> &Client::getChannels() const
{
    return _channels;
}

//Setters
void Client::setSocket(int socket)
{
    _socket = socket;
}

void Client::setNickname(const std::string &nickname)
{
    _nickname = nickname;
}

void Client::setUsername(const std::string &username)
{
    _username = username;
}

void Client::setRealname(const std::string &realname)
{
    _realname = realname;
}

void Client::setPassOk(bool value)
{
    _passOk = value;
}

void Client::setHasNick(bool value)
{
    _hasNick = value;
}

void Client::setHasUser(bool value)
{
    _hasUser = value;
}

void Client::setAuthenticated(bool value)
{
    _authenticated = value;
}

//Buffer
void Client::appendBuffer(const std::string &data)
{
    _buffer += data;
}

void Client::clearBuffer()
{
    _buffer.clear();
}

// Channels
void Client::addChannel(Channel *channel)
{
    _channels.insert(channel);
}

void Client::removeChannel(Channel *channel)
{
    _channels.erase(channel);
}

bool Client::isInChannel(Channel *channel) const
{
    std::set<Channel *>::const_iterator it;

    it = _channels.find(channel);

    if (it != _channels.end())
        return true;
    return false;
}
