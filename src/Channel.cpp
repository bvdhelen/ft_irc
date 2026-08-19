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

// Clients
void Channel::addClient(Client *client)
{
	_clients.insert(client);
}

void Channel::removeClient(Client *client)
{
	_clients.erase(client);
	_operators.erase(client);
}

bool Channel::hasClient(Client *client) const
{
	return _clients.find(client) != _clients.end();
}

// para que el server se pueda enterar de que tiene que borrar el canal (cuando se va el ultimo cliente)
bool Channel::isEmpty() const
{
	return _clients.empty();
}

// Operators
// el comando tiene que comprobar que el cliente este en el canal
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

// Topic
void Channel::setTopic(const std::string &topic)
{
	_topic = topic;
}

const std::string &Channel::getTopic() const
{
	return _topic;
}

// Modes - invite only
void Channel::setInviteOnly(bool value)
{
	_inviteOnly = value;
}

bool Channel::isInviteOnly() const
{
	return _inviteOnly;
}

// Modes - protected topic
void Channel::setProtectedTopic(bool value)
{
	_protectedTopic = value;
}

bool Channel::isProtectedTopic() const
{
	return _protectedTopic;
}

// mode - password
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

// el comando se encarga de comprobar si el canal tiene o no contraseña
bool Channel::checkPassword(const std::string &password) const
{
	return _password == password;
}

// mode - user limit
// si un canal no tenia limite y le ponen un limite menor al numero de clientes que tiene conserva a los clientes
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

// el canal puede tener más clientes del limite si ya estaban ahi antes de ponerlo
bool Channel::isFull() const
{
	return hasUserLimit() && _clients.size() >= _userLimit;
}

// exception
const char *Channel::NameTooLongException::what() const throw()
{
	return "Channel name cannot exceed 50 characters";
}
