# Compiler and flags
CC := cc
CFLAGS := -Wall -Wextra -Werror -I./includes -I./libft -I./minilibx-linux
LDFLAGS := -L./libft -L./minilibx-linux -lft -lmlx -lXext -lX11 -lm

# Executable name
NAME := cub3d

# Directories
SRC_DIR := src
OBJ_DIR := obj
LIBFT_DIR := libft
MLX_DIR := minilibx-linux

# Libraries
LIBFT := $(LIBFT_DIR)/libft.a
MLX := $(MLX_DIR)/libmlx.a

# Find mandatory sources (exclude test files, bonus files, and disabled files)
SRC := $(shell find $(SRC_DIR) -name '*.c' ! -name '*_bonus.c' ! -name 'test_*.c' ! -name '*.disabled.c' ! -name '*.diasbled.c')
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Bonus sources
BONUS_SRC := $(shell find $(SRC_DIR) -name '*_bonus.c')
BONUS_OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(BONUS_SRC))

# Colors

RED      = \033[0;31m
GREEN    = \033[0;32m
YELLOW   = \033[0;33m
BLUE     = \033[0;34m
CYAN     = \e[0;36m
GRAY     = \e[0;37m
NC       = \033[0m 

# Default rule
all: $(LIBFT) $(MLX) $(NAME)

# Build libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Build minilibx
$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@echo "*********************"
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)
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
bonus: $(LIBFT) $(MLX) $(OBJ) $(BONUS_OBJ)
	@echo "*********************"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(BONUS_OBJ) $(LDFLAGS)
	@echo -e "$(GREEN)| Linked $(NAME) with bonus |$(RESET)"
	@echo "*********************"

# Clean object files
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@echo -e "$(GREEN)Cleaned object files$(RESET)"

# Clean everything
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) clean
	@echo -e "$(GREEN)Removed $(NAME)$(RESET)"

# Rebuild everything
re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re bonus
