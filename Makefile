# Compiler and flags
CC := cc
CFLAGS := -Wall -Wextra -Werror

# Executable name
NAME := cube3d

# Directories
SRC_DIR := src
OBJ_DIR := obj

# Find mandatory sources (exclude test files and bonus files)
SRC := $(shell find $(SRC_DIR) -name '*.c' ! -name '*_bonus.c' ! -name 'test_*.c')
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Bonus sources
BONUS_SRC := $(shell find $(SRC_DIR) -name '*_bonus.c')
BONUS_OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(BONUS_SRC))

# Colors
GREEN := \033[1;32m
RED := \033[1;31m
RESET := \033[0m

# Default rule
all: $(NAME)

$(NAME): $(OBJ)
	@echo "*********************"
	$(CC) $(CFLAGS) -o $@ $^
	@echo -e "$(GREEN)| Linked $(NAME) |$(RESET)"
	@echo "*********************"

# Compile rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@if [ -f $< ]; then \
		mkdir -p $(dir $@); \
		$(CC) $(CFLAGS) -c $< -o $@; \
		echo -e "$(GREEN)| Compiled $(notdir $@) |$(RESET)"; \
	else \
		echo -e "$(RED)$(notdir $<) does not exist$(RESET)"; \
	fi

# Bonus rule
bonus: $(OBJ) $(BONUS_OBJ)
	@echo "*********************"
	$(CC) $(CFLAGS) -o $(NAME) $^
	@echo -e "$(GREEN)| Linked $(NAME) with bonus |$(RESET)"
	@echo "*********************"

# Clean object files
clean:
	@rm -rf $(OBJ_DIR)
	@echo -e "$(GREEN)Cleaned object files$(RESET)"

# Clean everything
fclean: clean
	@rm -f $(NAME)
	@echo -e "$(GREEN)Removed $(NAME)$(RESET)"

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re bonus
