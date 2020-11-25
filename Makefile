
NAME=miniRT

MLX_NAME=libmlx.a
MLX_DIR=miniLibX/
MLX=$(MLX_DIR)$(MLX_NAME)

LIBFT_NAME=libft.a
LIBFT_DIR=libft/
LIBFT=$(LIBFT_DIR)$(LIBFT_NAME)

DEVICE_NAME=libdevice.a
DEVICE_DIR=device/
DEVICE=$(DEVICE_DIR)$(DEVICE_NAME)

FLAGS=\
-framework OpenGL -framework AppKit \
-Wall -Wextra -Werror \
-I. -I$(LIBFT_DIR) -I$(MLX_DIR) -I$(DEVICE_DIR) -Iget_next_line/

SRC=
OBJ=$(SRC:.c=.o)
HEADERS=minirt.h

all: $(NAME)

$(SRC): $(HEADERS)
$(OBJ): $(MLX) $(LIBFT) $(DEVICE)
%.o: %.c
	gcc $(FLAGS) -c $(MLX) $(LIBFT) $(DEVICE) $< -o $@

$(NAME): $(MLX) $(LIBFT) $(DEVICE)
$(NAME): main.c $(HEADERS)
$(NAME): $(OBJ)
	gcc main.c $(FLAGS) -o $(NAME) $(OBJ) $(MLX) $(LIBFT) $(DEVICE)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR) part1
	$(MAKE) -C $(LIBFT_DIR) d

$(DEVICE):
	$(MAKE) -C $(DEVICE_DIR)

clean:
	rm -rf $(OBJ) main.o
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(MLX_DIR) fclean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
