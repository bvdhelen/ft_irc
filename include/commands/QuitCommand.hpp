#ifndef QUITCOMMAND_HPP
# define QUITCOMMAND_HPP

# include "Replies.hpp"
# include "Command.hpp"
# include "Client.hpp"

class QuitCommand : public Command
{
    public:
        QuitCommand(const std::vector<std::string> &params);
        ~QuitCommand();

        void execute(Server &server, Client &client);
};

#endif
