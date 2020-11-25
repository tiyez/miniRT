
NAME=miniRT
MLX_NAME=libmlx.a
MLX_DIR=miniLibX/
MLX=$(MLX_DIR)$(MLX_NAME)

FLAGS=-framework OpenGL -framework AppKit -I. -Wall -Wextra -Werror -Wno-deprecated-declarations

SRC=
OBJ=$(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	gcc $(FLAGS) $(MLX) $< -o $@

$(NAME): $(MLX) $(OBJ) main.c
	gcc main.c $(FLAGS) -o $(NAME) $(OBJ) $(MLX)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -rf $(OBJ) main.o
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)

re: fclean all
