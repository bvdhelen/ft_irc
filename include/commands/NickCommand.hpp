#ifndef NICKCOMMAND_HPP
# define NICKCOMMAND_HPP

# include "Command.hpp"

class NickCommand : public Command
{
	private:
		void notifyClients(Server &server, Client &client, std::string oldNickname, std::string newNickname);
		bool isValidNickname(const std::string &nickname);
		bool isNicknameInUse(Server &server, std::string nickname);
	public:
		NickCommand(const std::vector<std::string> &params);
		~NickCommand();

		void execute(Server &server, Client &client);
};

#endif
