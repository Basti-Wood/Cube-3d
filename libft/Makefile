# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sholz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/10 14:08:36 by sholz             #+#    #+#              #
#    Updated: 2025/10/09 14:00:00 by sholz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# === CONFIGURATION ============================================================

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
NAME		= libft.a
HEAD		= libft.h

# === FILES ====================================================================

SRCS		= $(wildcard *.c)
OBJS		= $(SRCS:.c=.o)

# === COLORS ===================================================================

GREEN		= \033[1;32m
BLUE		= \033[1;34m
YELLOW		= \033[1;33m
RED			= \033[1;31m
RESET		= \033[0m

BAR			= "=========================================="

# === RULES ====================================================================

all: header $(NAME)

header:
	@echo "$(BLUE)------ Libft Compilation ------$(RESET)"
	@echo $(BAR)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "$(GREEN)✅ Library '$(NAME)' created successfully!$(RESET)"
	@echo $(BAR)

%.o: %.c $(HEAD)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW)| $(notdir $@) created |$(RESET)"

clean:
	@rm -f $(OBJS)
	@echo "$(RED)🧹 Object files removed.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)💥 Library $(NAME) removed.$(RESET)"

re: fclean all

so:
	@$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS)
	@$(CC) -nostartfiles -shared -o libft.so $(OBJS)
	@echo "$(GREEN)🔗 Shared library 'libft.so' created.$(RESET)"

.PHONY: all clean fclean re so header
