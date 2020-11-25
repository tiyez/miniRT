
NAME=miniRT
MLX_NAME=libmlx.a
MLX_DIR=miniLibX/
MLX=$(MLX_DIR)$(MLX_NAME)
LIBFT_NAME=libft.a
LIBFT_DIR=libft/
LIBFT=$(LIBFT_DIR)$(LIBFT_NAME)

FLAGS=\
-framework OpenGL -framework AppKit \
-I. -Wall -Wextra -Werror

SRC=
OBJ=$(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	gcc $(FLAGS) $(MLX) $(LIBFT) $< -o $@

$(NAME): $(MLX)
$(NAME): $(LIBFT)
$(NAME): $(OBJ) main.c
	gcc main.c $(FLAGS) -o $(NAME) $(OBJ) $(MLX) $(LIBFT)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR) part1
	$(MAKE) -C $(LIBFT_DIR) d

clean:
	rm -rf $(OBJ) main.o
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(MLX_DIR) fclean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
