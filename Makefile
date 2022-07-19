NAME		=	webserv

CC			=	c++ -std=c++98
CFLAGS		=	-Wall -Werror -Wextra

# HEADER_DIR	=	./include
# SRC_DIR		=	./src
# OBJ_DIR		=	./obj

HEADER		=	fdhandler.hpp request.hpp requesthandler.hpp response.hpp selector.hpp server.hpp session.hpp utils.hpp utils2.hpp webserv.hpp \
				./cgi/CGI.hpp ./config/AConfig.hpp ./config/ConfigServer.hpp ./config/Location.hpp

SRC			=	main.cpp request.cpp requesthandler.cpp server.cpp session.cpp utils.cpp utils2.cpp \
				./cgi/CGI.cpp ./config/AConfig.cpp ./config/parser_config.cpp

# OBJ			=	$(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))
OBJ=$(SRC:.cpp=.o)

%.o: %.cpp $(HEADERS)
	$(CC) -c -o $@ $< 

RM_DIR		=	rm -rf
RM_FILE		=	rm -f

#COLORS
C_NO		=	"\033[00m"
C_OK		=	"\033[32m"
C_GOOD		=	"\033[32m"

#DEBUG
SUCCESS		=	$(C_GOOD)SUCCESS$(C_NO)
OK			=	$(C_OK)OK$(C_NO)

all			:	$(NAME)

# $(OBJ)		: 	| $(OBJ_DIR)	

# $(OBJ_DIR)	:
# 				@mkdir -p $(OBJ_DIR)
		

$(NAME)		:	$(OBJ) $(HEADER)
				$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
				@echo "\tCompiling...\t" [ $(NAME) ] $(SUCCESS)

clean		:
				@$(RM_DIR) $(OBJ)
				@echo "\tCleaning...\t" [ $(OBJ_DIR) ] $(OK)

fclean		:	clean
				@$(RM_FILE) $(NAME)
				@echo "\tDeleting...\t" [ $(NAME) ] $(OK)

re			:	fclean all

.PHONY		:	all, clean, fclean, re, test