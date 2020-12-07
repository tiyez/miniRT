
NAME=miniRT

MLX_NAME=libmlx.dylib
MLX_DIR=minilibx/
MLX_REMOTE=$(MLX_DIR)$(MLX_NAME)
MLX=$(MLX_NAME)

GNL_NAME=libgnl.a
GNL_DIR=get_next_line/
GNL=$(GNL_DIR)$(GNL_NAME)

LIBFT_NAME=libft.a
LIBFT_DIR=libft/
LIBFT=$(LIBFT_DIR)$(LIBFT_NAME)

FLAGS=\
-O2 -DNDEBUG\
-Wall -Wextra -Werror \
-I. -I$(LIBFT_DIR) -I$(MLX_DIR) -Iget_next_line

SRC=\
bmp.c\
clip.c\
color.c\
key.c\
line.c\
movement.c\
raytrace.c\
raytrace2.c\
render.c\
rgb.c\
scene.c\
select.c\
square.c\
util.c\
parse.c\
parse1.c\
parse2.c\
error.c\
free.c\
aabb.c\
aabb2.c
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
	@$(MAKE) -C $(MLX_DIR)
	@$(MAKE) -C $(GNL_DIR)
	@$(MAKE) $(NAME)

$(SRC): $(HEADERS)
$(OBJ): $(LIBFT) $(HEADERS)
%.o: %.c
	gcc $(FLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(MLX) $(GNL)
$(NAME): main.c $(HEADERS)
$(NAME): $(OBJ)
	gcc main.c $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX) $(GNL) -framework Metal -framework AppKit

$(MLX_REMOTE):
	@$(MAKE) -C $(MLX_DIR)
$(MLX): $(MLX_REMOTE)
	cp $(MLX_REMOTE) .

clean:
	rm -rf $(OBJ) main.o
	@$(MAKE) -C $(MLX_DIR) clean
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(GNL_DIR) clean

fclean: clean
	rm -rf $(NAME)
	@$(MAKE) -C $(MLX_DIR) fclean
	rm -rf $(MLX)
	rm -rf save.bmp
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(GNL_DIR) fclean

re: fclean all
