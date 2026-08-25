#ifndef TOPIC_COMMAND_HPP
# define TOPIC_COMMAND_HPP

# include "Command.hpp"

class TopicCommand : public Command
{
	private:
		void sendCurrentTopic(Server &server, Client &client, Channel *channel);
		void setTopic(Server &server, Client &client, Channel *channel, const std::string &topic);
	public:
		TopicCommand(const std::vector<std::string> &params);
		~TopicCommand();

		void execute(Server &server, Client &client);
};

#endif
