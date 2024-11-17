# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malee <malee@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 09:23:00 by malee             #+#    #+#              #
#    Updated: 2024/11/18 00:11:31 by malee            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFILES = main.c checker.c mise_en_place.c simulation.c routine.c \
			routine_utils.c cleanup.c time_utils.c utils.c monitor.c
SRC_DIR = ./srcs
SRCS = $(addprefix $(SRC_DIR)/,$(CFILES))
OBJS = $(addprefix $(OBJ_DIR)/,$(CFILES:.c=.o))
OBJ_DIR = ./obj
CC = cc
INCLUDE_DIR = ./includes
CFLAGS = -Wall -Wextra -Werror -g -I$(INCLUDE_DIR)

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m

all: $(OBJ_DIR) $(NAME)

# Object compilation
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW)Compiling $<$(RESET)"

# Main program compilation
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) created successfully.$(RESET)"

# Directory creation
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(GREEN)$(OBJ_DIR) directory created.$(RESET)"

# Clean up
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Object files cleaned successfully.$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(GREEN)All executables removed successfully.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
