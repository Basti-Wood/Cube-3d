NAME = game 
CC = gcc
OBJS = $(SRCS:.c=.o)

LFLAGS = -L./libs/libft -lft -L./libs/mlx -lmlx -lXext -lX11 -lm -lz
INCS = libs/libft/libft.a -I./libs/libft libs/mlx/libmlx.a incs/game.h
SRCS = srcs/main.c srcs/init.c srcs/map.c srcs/key_event.c srcs/movement.c srcs/collision.c srcs/ray.c \
	srcs/draw_static.c srcs/draw_ambulatory.c srcs/walker_texas_ranger.c srcs/debug.c srcs/utils.c \
	srcs/texture.c srcs/texture_utils.c

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

fclean:
	rm -rf $(OBJS)
	rm -rf $(NAME)
