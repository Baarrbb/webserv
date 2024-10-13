# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/06 21:59:59 by marvin            #+#    #+#              #
#    Updated: 2024/10/10 17:45:57 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
_BLUE=\033[0;34m
_ROSE=\x1b[38;5;213m
_NEW_BLUE=\x1b[38;5;80m
_NEW_YELLOW=\x1b[38;5;228m
_GREEN_BOLD=\033[1;32m
_LIGHT_GREY=\x1b[38;5;242m
_PURPLE_UNDER=\033[0;4m\x1b[38;5;093m

# Reset colors
_END=\033[0;0m

MAKEFLAGS += --no-print-directory
OPTIONS_PRINTED = /tmp/options_printed_${USER}

SRC_DIR = srcs

SRC = \
	$(SRC_DIR)/RequestClient.cpp \
	$(SRC_DIR)/main.cpp


OBJ_DIR = $(SRC_DIR)/obj
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

NAME = webserv
INC = -I./headers

RM = rm -rf
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

all : $(NAME)

print_options : $(OPTIONS_PRINTED)

$(OPTIONS_PRINTED) :
	@ /bin/bash -c "echo"
	@ /bin/bash -c "echo -e \"$(_ROSE)Compiling options$(_END) :  $(CC) $(CFLAGS)\""
	@ /bin/bash -c "echo"
	@ touch $(OPTIONS_PRINTED)

$(NAME) : $(OPTIONS_PRINTED) $(OBJ_DIR) $(OBJ)
	@ /bin/bash -c "echo"
	@ /bin/bash -c "echo -e \"$(_NEW_BLUE)Linking files creating binary $(NAME)$(_END)\""
	@ /bin/bash -c "echo -e \"$(CC) $(CFLAGS) $(notdir $(OBJ) $(LIBFT))\""
	@ $(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIB) -o $(NAME)
	@ /bin/bash -c "echo"
	@ /bin/bash -c "echo -e \"$(_GREEN_BOLD)[DONE]$(_END)\"" 

$(OBJ_DIR) :
	@ mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@ /bin/bash -c "printf \"$(_BLUE)Compiling$(_END) %-21s --> %-21s\n\" $(notdir $<) $(notdir $@)"
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $(INC) -c $< -o $@

clean :
	@ /bin/bash -c "echo -e \"$(_LIGHT_GREY)Cleaning object files$(_END)\""
	@ $(RM) $(OBJ_DIR)
	@ $(RM) $(OBJ_DIR_BONUS)
	@ $(RM) $(OPTIONS_PRINTED)

fclean : clean
	@ /bin/bash -c "echo -e \"$(_LIGHT_GREY)Cleaning binary$(_END)\""
	@ $(RM) $(NAME)
	@ $(RM) $(NAME_BONUS)

re : fclean all
