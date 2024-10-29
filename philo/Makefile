NAME = philo
INCLUDE_DIR = includes
CFILES = main.c init_utils.c routines.c routine_utils.c utils.c utils2.c
SRC_DIR = srcs
SRCS = $(addprefix $(SRC_DIR)/,$(CFILES))
CC = cc
# -O1, -O2, -O3, and -Ofast Increasing level of compiler aggresiveness
# set lower if encountering bugs -Os for space priority
CFLAGS = -Wall -Wextra -Werror -g
OBJ_DIR = ./obj
OBJS = $(addprefix $(OBJ_DIR)/, $(CFILES:%.c=%.o))

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) created successfully.$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(GREEN)$(OBJ_DIR) directory created.$(RESET)"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(addprefix -I,$(INCLUDE_DIR)) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)$(NAME) object files cleaned successfully.$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(GREEN)$(NAME) removed successfully.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
