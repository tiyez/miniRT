
NAME=miniRT

MLX_NAME=libmlx.dylib
#MLX_NAME=libmlx.a
MLX_DIR=minilibx/
MLX_REMOTE=$(MLX_DIR)$(MLX_NAME)
MLX=$(MLX_NAME)
#MLX=$(MLX_DIR)$(MLX_NAME)

GNL_NAME=libgnl.a
GNL_DIR=get_next_line/
GNL=$(GNL_DIR)$(GNL_NAME)

LIBFT_NAME=libft.a
LIBFT_DIR=libft/
LIBFT=$(LIBFT_DIR)$(LIBFT_NAME)

DEVICE_NAME=libdevice.a
DEVICE_DIR=device/
DEVICE=$(DEVICE_DIR)$(DEVICE_NAME)

FLAGS=\
-O2 \
-Wall -Wextra -Werror \
-I. -I$(LIBFT_DIR) -I$(MLX_DIR) -I$(DEVICE_DIR) -Iget_next_line/

SRC=\
parse.c\
error.c\
free.c
OBJ=$(SRC:.c=.o)
HEADERS=minirt.h

all:
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(LIBFT_DIR) part1
	@$(MAKE) -C $(LIBFT_DIR) fd
	@$(MAKE) -C $(LIBFT_DIR) b
	@$(MAKE) -C $(LIBFT_DIR) vs
	@$(MAKE) -C $(LIBFT_DIR) vmath_ext
	@$(MAKE) -C $(LIBFT_DIR) vmath_quat
	@$(MAKE) -C $(LIBFT_DIR) intersection
	@$(MAKE) -C $(DEVICE_DIR)
	@$(MAKE) -C $(MLX_DIR)
	@$(MAKE) -C $(GNL_DIR)
	@$(MAKE) $(NAME)

$(SRC): $(HEADERS)
$(OBJ): $(LIBFT) $(DEVICE) $(HEADERS)
%.o: %.c
	gcc $(FLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(DEVICE) $(MLX) $(GNL)
$(NAME): main.c $(HEADERS)
$(NAME): $(OBJ)
	gcc main.c $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(DEVICE) $(MLX) $(GNL) -framework Metal -framework AppKit

$(MLX_REMOTE):
	$(MAKE) -C $(MLX_DIR)
$(MLX): $(MLX_REMOTE)
	cp $(MLX_REMOTE) .
#$(MLX):
#	$(MAKE) -C $(MLX_DIR)

clean:
	rm -rf $(OBJ) main.o
	@$(MAKE) -C $(MLX_DIR) clean
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(DEVICE_DIR) clean
	@$(MAKE) -C $(GNL_DIR) clean

fclean: clean
	rm -rf $(NAME)
	@$(MAKE) -C $(MLX_DIR) fclean
	rm -rf $(MLX)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(DEVICE_DIR) fclean
	@$(MAKE) -C $(GNL_DIR) fclean

re: fclean all
