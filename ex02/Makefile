# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmory <tmory@student.42antananarivo.mg>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 14:28:55 by tmory             #+#    #+#              #
#    Updated: 2026/01/26 17:22:21 by tmory            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CPP = c++
CPPFLAG = -Wall -Wextra -Werror -std=c++98 -g
CPPNOFLAG = -Wall -Wextra -Werror
MAKE = make
MAKECLEAN = make clean
NAMENOFLG = PmergeMe_noStd
RM = rm
SRC = main.cpp PmergeMe.cpp\

OBJ_DIR  = obj
OBJ_DIR_NFLG  = obj_nofl
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:%.cpp=%.o))
OBJNFLG = $(addprefix $(OBJ_DIR_NFLG)/,$(SRC:%.cpp=%.o))
LIBRARY = PmergeMe_lib.a
NAME = PmergeMe

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rcs $(LIBRARY) $(OBJ)
	@echo "\033[0m"
	@echo "library PmergeMe_lib.a created"
	$(CPP) $(CPPFLAG) $(LIBRARY) -o $(NAME)
	@echo "\033[90m[\033[32;1;5mSuccess\033[0m\033[90m]\033[32m Program 'PmergeMe' successfully compiled.\033[0m"

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	@echo -n "\033[90m"
	$(CPP) $(CPPFLAG) -c $< -o $@ 

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_DIR_NFLG)
	rm -f $(LIBRARY)
	@echo "\033[90m[\033[91;5;1mDeleting\033[0m\033[90m]\033[31m Object folder deleted\033[0m"

fclean: clean
	rm -f $(NAME)
	rm -f $(NAMENOFLG)
	@echo "\033[90m[\033[91;5;1mDeleting\033[0m\033[90m]\033[31m Objects, executable and library deleted\033[0m"

noflag: $(NAMENOFLG)

$(NAMENOFLG): $(OBJNFLG)
	@ar -rcs $(LIBRARY) $(OBJNFLG)
	@echo "\033[0m"
	@echo "library PmergeMe_lib.a created"
	$(CPP) $(CPPNOFLAG) $(LIBRARY) -o $(NAMENOFLG)
	@echo "\033[90m[\033[32;1;5mSuccess\033[0m\033[90m]\033[32m Program 'PmergeMe_noStd' successfully compiled.\033[0m"

$(OBJ_DIR_NFLG)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR_NFLG)
	@echo -n "\033[90m"
	$(CPP) $(CPPNOFLAG) -c $< -o $@ 



re: fclean $(NAME)
.PHONY:  all clean fclean re
