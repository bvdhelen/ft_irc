#include "Server.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
        return 1;
    }
    char *end;
    int port = std::strtol(argv[1], &end, 10);
    if (argv[1][0] == '\0' || *end != '\0')
    {
        std::cerr << "Error: invalid port." << std::endl;
        return 1;
    }
    if (port < 1024 || port > 65535)
    {
        std::cerr << "Error: port must be a number in the range [1024, 65535]."<< std::endl;
        return 1;
    }
    std::string password = argv[2];
    if (password.empty())
    {
        std::cerr << "Error: password cannot be empty."<< std::endl;
        return 1;
    }
/*
    try
    {
        Server server(port, password);
    
        server.initServer();
        server.run();
    }
    catch(const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    */
    
    return 0;
}
