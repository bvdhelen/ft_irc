#include "TopicCommand.hpp"
#include "Channel.hpp"

TopicCommand::TopicCommand(const std::vector<std::string> &params)
{
	// TODO
}

TopicCommand::~TopicCommand(void)
{
}

void TopicCommand::execute(Server &server, Client &client)
{
	// 1. Comprobar número de parámetros
	if (_params.size() < 1 || _params.size() > 2)
	{
		// TODO error
	}
	
	// 2. Obtener el canal
	Channel *channel = server.getChannelByName(_params[0]);

	// 3. Comprobar que existe
	if (channel == NULL)
	{
		return ; // TODO error
	}

	// 4. Comprobar que el cliente pertenece al canal
	if (!channel->hasClient(&client))
		return ; // TODO error

	// 5. Si solo viene el canal:
	//      enviar topic actual
	if (_params.size() == 1)
	{
		channel->getTopic(); // TODO send
		return ;
	}
	
	// 6. Si viene un topic:
	//      si +t -> comprobar operator
	//      cambiar topic
	//      enviar TOPIC a los usuarios del canal
	if (channel->isProtectedTopic() && !channel->isOperator(&client))
		return ; // TODO error
		
	// TODO cambiar topic
}
