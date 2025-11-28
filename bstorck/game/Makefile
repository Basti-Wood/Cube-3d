NAME = game 
CC = gcc
OBJ = $(SRC:.c=.o)

LFLAGS = -L./includes/mlx -lmlx -lXext -lX11 -lm -lz
INCLUDES = includes/mlx/libmlx.a
SRC = src/main.c src/init.c src/map.c src/sonar_debug.c src/key_event.c src/ray.c src/settings.c \
	src/draw_static.c src/draw_ambulatory.c src/utils.c src/walker_texas_ranger.c src/movement.c src/collision.c

all: $(NAME)

mlx:
	git clone https://github.com/42Paris/minilibx-linux.git ./includes/mlx
	make -C ./includes/mlx

$(NAME): $(OBJ)
	$(CC) $(SRC) -o $(NAME) $(INCLUDES) $(LFLAGS)

re:
	make fclean
	make all

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)
