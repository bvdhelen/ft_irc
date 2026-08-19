#ifndef TOPIC_COMMAND_HPP
# define TOPIC_COMMAND_HPP

# include "Command.hpp"

/**
 * Command: TOPIC
 * Parameters: <channel> [ <topic> ]
 */
class TopicCommand : public Command
{
	public:
		TopicCommand(const std::vector<std::string> &params);
		~TopicCommand();

		void execute(Server &server, Client &client);
};

#endif
