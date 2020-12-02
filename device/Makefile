
NAME=libdevice.a

MLX_DIR=../miniLibX/
MLX_NAME=libmlx.a
MLX_REMOTE=$(MLX_DIR)$(MLX_NAME)
MLX=$(MLX_NAME)

LIBFT_NAME=libft.a
LIBFT_DIR=../libft/
LIBFT=$(LIBFT_DIR)$(LIBFT_NAME)

SRC=\
device.c\
event.c\
getters.c\
hook.c\
image.c
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

$(NAME): $(OBJ)
	ar rc $(NAME) $?

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
