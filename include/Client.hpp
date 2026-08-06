#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ft_irc.hpp"

class Channel;

class Client
{
    private:
        // Identificador del cliente
        int _socket;

        std::string _nickname;
        std::string _username;
        std::string _realname;

        // Buffer donde se almacenan los datos recibidos
        std::string _buffer;

        // Estado del registro
        bool _passOk;
        bool _hasNick;
        bool _hasUser;
        bool _authenticated;

        // Canales a los que pertenece
        std::set<Channel *> _channels;

    public:
        Client(int socket);
        ~Client();

        //Getters
        int getSocket() const;
        const std::string &getNickname() const;
        const std::string &getUsername() const;
        const std::string &getRealname() const;
        const std::string &getBuffer() const;
        bool getPassOk() const;
        bool getHasNick() const;
        bool getHasUser() const;
        bool isAuthenticated() const;

        const std::set<Channel *> &getChannels() const;

        //Setters
        void setFd(int socket);
        void setNickname(const std::string &nickname);
        void setUsername(const std::string &username);
        void setRealname(const std::string &realname);

        void setPassOk(bool value);
        void setHasNick(bool value);
        void setHasUser(bool value);
        void setAuthenticated(bool value);

        //Buffer
        void appendBuffer(const std::string &data);
        void clearBuffer();

        // Channels
        void addChannel(const Channel *channel);
        void removeChannel(const Channel *channel);
        bool isInChannel(const Channel *channel) const;

};

#endif
