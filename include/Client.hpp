#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "ft_irc.hpp"
# include "Channel.hpp"

class Client
{
    private:
        int _socket;

        std::string _nickname;
        std::string _username;
        std::string _realname;
        std::string _host;

        std::string _buffer;

        bool _passOk;
        bool _hasNick;
        bool _hasUser;
        bool _authenticated;
		bool _requestedDisconnect;
		std::string _quitMessage;

        std::set<Channel *> _channels;

    public:
        Client(int socket);
        ~Client();

        // Getters
        int getSocket() const;
        const std::string &getNickname() const;
        const std::string &getUsername() const;
        const std::string &getRealname() const;
        const std::string &getHost() const;
        const std::string &getBuffer() const;
        bool getPassOk() const;
        bool getHasNick() const;
        bool getHasUser() const;
        bool isAuthenticated() const;
		bool hasRequestedDisconnection() const;
		const std::string &getQuitMessage() const;

        const std::set<Channel *> &getChannels() const;

        // Setters
        void setSocket(int socket);
        void setNickname(const std::string &nickname);
        void setUsername(const std::string &username);
        void setRealname(const std::string &realname);
        void setHost(const std::string &host);

        void setPassOk(bool value);
        void setHasNick(bool value);
        void setHasUser(bool value);
        void setAuthenticated(bool value);
		void setRequestedDisconnection(bool value);
		void setQuitMessage(const std::string &message);

        // Buffer
        void appendBuffer(const std::string &data);
        void clearBuffer();
        bool hasCommandBuffer() const;
        std::string getCommandFromBuffer();

        // Channels
        void addChannel(Channel *channel);
        void removeChannel(Channel *channel);
        bool isInChannel(Channel *channel) const;
        void disconnect();
};

#endif
