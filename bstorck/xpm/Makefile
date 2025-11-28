NAME = game 
CC = gcc
OBJS = $(SRCS:.c=.o)

LFLAGS = -L./libs/mlx -lmlx -L./libs/libft -lft -lXext -lX11 -lm -lz
INCS = libs/mlx/libmlx.a libs/libft/libft.a incs/game.h libs/libft/get_next_line.h
SRCS = srcs/main.c srcs/texture.c srcs/texture_utils.c srcs/utils.c

all: $(NAME)

mlx:
	git clone https://github.com/42Paris/minilibx-linux.git ./libs/mlx
	make -C ./libs/mlx

$(NAME): $(OBJS)
	$(CC) $(SRCS) -o $(NAME) $(INCS) $(LFLAGS)

re:
	make fclean
	make all

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(OBJS)
	rm -rf $(NAME)
