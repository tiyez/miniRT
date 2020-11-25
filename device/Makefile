
NAME=libdevice.a

MLX_DIR=../miniLibX/
MLX_NAME=libmlx.a
MLX=$(MLX_DIR)$(MLX_NAME)

LIBFT_NAME=libft.a
LIBFT_DIR=../libft/
LIBFT=$(LIBFT_DIR)$(LIBFT_NAME)

SRC=\
device.c\
event.c\
getters.c\
hook.c
OBJ=$(SRC:.c=.o)
HEADERS=\
device_private.h

FLAGS=\
-c\
-Wall -Wextra -Werror \
-I. -I$(LIBFT_DIR) -I$(MLX_DIR)\

all: $(NAME)

%.o: %.c
	gcc $(FLAGS) $< -o $@

$(NAME): $(MLX) $(LIBFT)
$(NAME): $(OBJ)
	ar rc $(NAME) $?

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR) part1

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
