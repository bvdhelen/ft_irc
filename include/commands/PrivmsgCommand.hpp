#ifndef PRIVMSGCOMMAND_HPP
# define PRIVMSGCOMMAND_HPP

# include "Command.hpp"

class PrivmsgCommand : public Command
{
    public:
        PrivmsgCommand(const std::vector<std::string> &params);
        ~PrivmsgCommand();

        void execute(Server &server, Client &client);
};

#endif
