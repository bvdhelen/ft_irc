#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "ft_irc.hpp"

class Client;

class Channel
{
	private:
		std::string _name;
		std::string _topic;
		std::string _password;
		size_t _userLimit; // 0 means no limit

		std::set<Client *> _clients;
		std::set<Client *> _operators; // admins

		bool _inviteOnly;
		bool _protectedTopic;

	public:
		Channel(const std::string &name, const std::string &password = "");
		~Channel();

		// clients
		void addClient(Client *client);
		void removeClient(Client *client); //que no quede nadie dentro
		bool hasClient(Client *client) const;
		// TODO bool isEmpty() const;

		// operators
		void addOperator(Client *client);
		void removeOperator(Client *client);
		bool isOperator(Client *client) const;

		// topic
		void setTopic(const std::string &topic);
		const std::string &getTopic() const;

		// modes
                // mode - invite only
		void setInviteOnly(bool value);
		bool isInviteOnly() const;

		// mode - protected topic
		void setProtectedTopic(bool value);
		bool isProtectedTopic() const;

		// mode - password
		void setPassword(const std::string &password);
		void removePassword();
		bool hasPassword() const;
		bool checkPassword(const std::string &password) const;

		// mode - user limit
		void setUserLimit(size_t limit);
		void removeUserLimit(); //remove es set a 0
		bool hasUserLimit() const;
		bool isFull() const;
};

#endif
