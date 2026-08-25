#include "Channel.hpp"
#include "Client.hpp"

// Constructor
Channel::Channel(const std::string &name, const std::string &password)
				: _name(name),
					_topic(""),
					_password(password),
					_userLimit(0),
					_inviteOnly(false),
					_protectedTopic(false)
{
	if (_name.size() > 50)
		throw NameTooLongException();
}

// Destructor
Channel::~Channel()
{
}

// Getters
const std::string &Channel::getName() const
{
    return _name;
}

const std::string &Channel::getTopic() const
{
    return _topic;
}

const std::set<Client *> &Channel::getClients() const
{
    return _clients;
}

const std::set<Client *> &Channel::getOperators() const
{
    return _operators;
}

// Clients
void Channel::addClient(Client *client)
{
	_clients.insert(client);
}

void Channel::removeClient(Client *client)
{
	_clients.erase(client);
	_operators.erase(client);
	_invited.erase(client);
}

bool Channel::hasClient(Client *client) const
{
	return _clients.find(client) != _clients.end();
}

bool Channel::isEmpty() const
{
	return _clients.empty();
}

// Operators
void Channel::addOperator(Client *client)
{
	_operators.insert(client);
}

void Channel::removeOperator(Client *client)
{
	_operators.erase(client);
}

bool Channel::isOperator(Client *client) const
{
	return _operators.find(client) != _operators.end();
}

// Invite
void Channel::addInvited(Client *client)
{
    _invited.insert(client);
}

void Channel::removeInvited(Client *client)
{
    _invited.erase(client);
}

bool Channel::isInvited(Client *client) const
{
    return _invited.find(client) != _invited.end();
}

// Topic
void Channel::setTopic(const std::string &topic)
{
	_topic = topic;
}

// Mode - invite only
void Channel::setInviteOnly(bool value)
{
	_inviteOnly = value;
}

bool Channel::isInviteOnly() const
{
	return _inviteOnly;
}

// Mode - protected topic
void Channel::setProtectedTopic(bool value)
{
	_protectedTopic = value;
}

bool Channel::isProtectedTopic() const
{
	return _protectedTopic;
}

// Mode - password
void Channel::setPassword(const std::string &password)
{
	_password = password;
}

void Channel::removePassword()
{
	_password.clear();
}

bool Channel::hasPassword() const
{
	return !_password.empty();
}

bool Channel::checkPassword(const std::string &password) const
{
	return _password == password;
}

// Mode - user limit
void Channel::setUserLimit(size_t limit)
{
	_userLimit = limit;
}

void Channel::removeUserLimit()
{
	_userLimit = 0;
}

bool Channel::hasUserLimit() const
{
	return _userLimit != 0;
}

bool Channel::isFull() const
{
	return hasUserLimit() && _clients.size() >= _userLimit;
}

// Exception
const char *Channel::NameTooLongException::what() const throw()
{
	return "Channel name cannot exceed 50 characters";
}
