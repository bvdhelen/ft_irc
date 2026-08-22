#ifndef JOINCOMMAND_HPP
# define JOINCOMMAND_HPP

# include "Replies.hpp"
# include "Command.hpp"
# include "Channel.hpp"

class JoinCommand : public Command
{
    public:
        JoinCommand(const std::vector<std::string> &params);
        ~JoinCommand();

        void execute(Server &server, Client &client);
};

#endif
