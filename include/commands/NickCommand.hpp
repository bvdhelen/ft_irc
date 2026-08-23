#ifndef NICKCOMMAND_HPP
#define NICKCOMMAND_HPP

#include "commands/Command.hpp"
#include "Replies.hpp"

class NickCommand : public Command
{
	public:
		NickCommand(std::vector<std::string> params);
		~NickCommand();

		void notifyClients(Server& server, Client& client, std::string oldNickname, std::string newNickname);
		bool isValidNickname(const std::string &nickname);
		bool isNicknameInUse(Server& server, std::string nickname);
		void execute(Server& server, Client& client);
};

#endif
