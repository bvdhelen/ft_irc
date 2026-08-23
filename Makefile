# Nombre del programa
NAME = ircserv

# Compilador y banderas de compilación
CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98
INCLUDES = -Iinclude

# Carpeta para objetos
OBJ_DIR = obj

# Definir códigos de color
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
GREY = \033[0;90m
RESET = \033[0m

# Archivos fuente y archivos objeto
SRCS = src/main.cpp src/Client.cpp src/Channel.cpp src/Server.cpp src/parser/CommandParser.cpp src/parser/CommandFactory.cpp src/commands/Command.cpp src/commands/ModeCommand.cpp
OBJS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREY)Compiling...$(RESET)"
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo
	@echo "$(GREEN)<<< ft_irc compiled >>>$(RESET)"
	@echo

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo
	@echo "$(CYAN)<<< clean complete >>>$(RESET)"
	@echo

fclean: clean
	@rm -rf $(NAME)
	@echo "$(BLUE)<<< full clean complete >>>$(RESET)"
	@echo

re: fclean all

.PHONY: all clean fclean re
