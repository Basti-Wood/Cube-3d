NAME = game

CC = gcc

OBJS = $(SRCS:.c=.o)

LFLAGS = -L./libs/libft -lft -L./libs/mlx -lmlx -lXext -lX11 -lm -lz

INCS = libs/libft/libft.a -I./libs/libft libs/mlx/libmlx.a incs/game.h

SRCS = srcs/close+free.c srcs/collision.c srcs/dda.c srcs/draw_1.c srcs/draw_2.c \
	srcs/draw_line_loop.c srcs/game_loop.c srcs/get_functions.c srcs/hex_calc.c \
	srcs/key_event.c srcs/main.c srcs/map.c srcs/parse_helpers.c srcs/parse_xpm_file.c \
	srcs/presenter_loop.c srcs/utils.c srcs/walker_loop.c

all: $(NAME)

mlx:
	git clone https://github.com/42Paris/minilibx-linux.git ./libs/mlx
	make -C ./libs/mlx

$(NAME): $(OBJS)
	make -C ./libs/libft
	$(CC) $(SRCS) -o $(NAME) $(INCS) $(LFLAGS)

re:
	make fclean
	make all

clean:
	rm -rf $(OBJS)
	make fclean -C ./libs/libft

fclean:
	rm -rf $(OBJS)
	rm -rf $(NAME)
	make fclean -C ./libs/libft
