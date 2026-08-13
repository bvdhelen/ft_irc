#include "../include/Channel.hpp"
#include "../include/Client.hpp"

// Constructor
Channel::Channel(const std::string &name, const std::string &password)
        : _name(name),
          _topic(""),
          _password(password),
          _userLimit(0),
          _inviteOnly(false),
          _protectedTopic(false)
{
}

// Destructor
Channel::~Channel()
{
}

// Clients
void Channel::addClient(Client *client)
{
  // TODO ¿hacemos algo si viene a null o el cliente ya está en el canal?
  _clients.insert(client);
}

void Channel::removeClient(Client *client)
{
  // TODO ¿hacemos algo si viene a null o el cliente NO está en el canal?
  _clients.erase(client);
  _operators.erase(client);

  // TODO ¿como gestionamos el borrar el canal cuando se queda vacio?
}

bool Channel::hasClient(Client *client) const
{
  return _clients.find(client) != _clients.end();
}

// TODO para que el server se pueda enterar de que tiene que borrar el canal (cuando se va el ultimo cliente)
// bool Channel::isEmpty() const
// {
//   return _clients.empty();
// }

// Operators
void Channel::addOperator(Client *client)
{
  // TODO: decide what to do if client is NULL or not in the channel
  if (!hasClient(client))
    return;

  _operators.insert(client);
}

void Channel::removeOperator(Client *client)
{
  // TODO: decide what to do if client is NULL or not an operator
  _operators.erase(client);
}

bool Channel::isOperator(Client *client) const
{
  return _operators.find(client) != _operators.end();
}

// Topic
void Channel::setTopic(const std::string &topic)
{
  // TODO tenia max de chars?
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

bool Channel::checkPassword(const std::string &password) const
{
  // TODO que hacemos cuando no hay contraseña?
  return _password == password;
}

// mode - user limit
void Channel::setUserLimit(size_t limit)
{
  // TODO que pasa si un canal no tenia limite y le ponen un limite menor al numero de clientes que tiene?
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
  // TODO el >= depende del TODO de setUserLimit
  return hasUserLimit() && _clients.size() >= _userLimit;
}
