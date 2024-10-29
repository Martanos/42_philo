NAME = philo
INCLUDE_DIR = includes
CFILES = main.c init_utils.c routines.c routine_utils.c utils.c utils2.c
SRC_DIR = srcs
SRCS = $(addprefix $(SRC_DIR)/,$(CFILES))
CC = cc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g
TSAN_FLAGS = -fsanitize=thread
DRD_FLAGS = 
HELGRIND_FLAGS = 

# Directories
OBJ_DIR = ./obj
TEST_DIR = ./tests
TEST_OUTPUT = ./test_output

# Objects
OBJS = $(addprefix $(OBJ_DIR)/, $(CFILES:%.c=%.o))

# Test executables
TSAN_NAME = $(NAME)_tsan
DRD_NAME = $(NAME)_drd
HELGRIND_NAME = $(NAME)_helgrind

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m

# Default target
all: $(OBJ_DIR) $(NAME)

# Main program compilation
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) created successfully.$(RESET)"

# Thread Sanitizer version
tsan: CFLAGS += $(TSAN_FLAGS)
tsan: $(OBJ_DIR) $(TSAN_NAME)

$(TSAN_NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(TSAN_NAME) $(OBJS)
	@echo "$(GREEN)Thread Sanitizer version created successfully.$(RESET)"

# Test targets
test: test_setup basic_test race_test deadlock_test leak_test
	@echo "$(GREEN)All tests completed.$(RESET)"

test_setup:
	@mkdir -p $(TEST_OUTPUT)
	@echo "$(GREEN)Test environment setup complete.$(RESET)"

basic_test: $(NAME)
	@echo "$(YELLOW)Running basic functionality tests...$(RESET)"
	@./tests/basic_test.sh $(NAME) $(TEST_OUTPUT) || true

race_test: tsan
	@echo "$(YELLOW)Running race condition tests...$(RESET)"
	@./tests/race_test.sh $(TSAN_NAME) $(TEST_OUTPUT) || true

deadlock_test: $(NAME)
	@echo "$(YELLOW)Running deadlock tests...$(RESET)"
	@valgrind --tool=helgrind ./$(NAME) 4 410 200 200 > $(TEST_OUTPUT)/helgrind.txt 2>&1 || true

leak_test: $(NAME)
	@echo "$(YELLOW)Running memory leak tests...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) 4 410 200 200 > $(TEST_OUTPUT)/valgrind.txt 2>&1 || true

stress_test: $(NAME)
	@echo "$(YELLOW)Running stress tests...$(RESET)"
	@./tests/stress_test.sh $(NAME) $(TEST_OUTPUT) || true

# Directory creation
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(GREEN)$(OBJ_DIR) directory created.$(RESET)"

# Object compilation
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(addprefix -I,$(INCLUDE_DIR)) -c $< -o $@

# Create test scripts
setup_tests: 
	@mkdir -p $(TEST_DIR)
	@echo '#!/bin/bash\n\
	NAME=$$1\n\
	OUTPUT_DIR=$$2\n\
	\n\
	# Single philosopher test\n\
	./$$NAME 1 800 200 200 > $$OUTPUT_DIR/single.txt\n\
	# Even philosophers test\n\
	./$$NAME 4 410 200 200 > $$OUTPUT_DIR/even.txt\n\
	# Odd philosophers test\n\
	./$$NAME 5 410 200 200 > $$OUTPUT_DIR/odd.txt' > $(TEST_DIR)/basic_test.sh
	
	@echo '#!/bin/bash\n\
	NAME=$$1\n\
	OUTPUT_DIR=$$2\n\
	\n\
	# Rapid death test\n\
	./$$NAME 4 200 210 200 > $$OUTPUT_DIR/race1.txt\n\
	# Simultaneous meals test\n\
	./$$NAME 4 410 200 200 5 > $$OUTPUT_DIR/race2.txt\n\
	# Quick succession test\n\
	./$$NAME 4 200 100 100 > $$OUTPUT_DIR/race3.txt' > $(TEST_DIR)/race_test.sh
	
	@echo '#!/bin/bash\n\
	NAME=$$1\n\
	OUTPUT_DIR=$$2\n\
	\n\
	# High load test\n\
	./$$NAME 20 800 200 200 10 > $$OUTPUT_DIR/stress1.txt\n\
	# Maximum values test\n\
	./$$NAME 200 60000 60000 60000 1 > $$OUTPUT_DIR/stress2.txt\n\
	# Minimum values test\n\
	./$$NAME 2 60 60 60 1 > $$OUTPUT_DIR/stress3.txt' > $(TEST_DIR)/stress_test.sh
	
	@chmod +x $(TEST_DIR)/*.sh
	@echo "$(GREEN)Test scripts created successfully.$(RESET)"

# Cleanup targets
clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(TEST_OUTPUT)
	@echo "$(GREEN)Object files and test outputs cleaned successfully.$(RESET)"

fclean: clean
	@rm -rf $(NAME) $(TSAN_NAME) $(DRD_NAME) $(HELGRIND_NAME)
	@echo "$(GREEN)All executables removed successfully.$(RESET)"

re: fclean all

.PHONY: all clean fclean re test tsan test_setup basic_test race_test deadlock_test leak_test stress_test setup_tests
