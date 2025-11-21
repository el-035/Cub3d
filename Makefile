NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I/usr/include -Imlx_linux

SRC = main.c exit.c movements.c calculations.c init_stuff.c visuals.c calculations_utils.c parse/helpers.c parse/helpers2.c parse/validate_map.c parse/init.c parse/map.c parse/parse.c parse/validation.c parse/parse_colors.c parse/parse_textures.c keys.c mini_map.c
OBJ = $(patsubst %.c,obj/%.o,$(SRC))

LIBFT = libft/libft.a
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -g -L$(LIBFT_DIR) -lft -Lmlx_linux -Imlx_Linux -lmlx -lXext -lX11 -lm -lz -o $(NAME) $(LIBFT)

$(LIBFT):
	make -C libft
	
# $(NAME): $(OBJ)
# 	make -C libft
# 	$(CC) $(OBJ) -o $(NAME) libft/libft.a
# 	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) $(LIBFT)

obj/%.o: %.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

obj/exec/%.o: src/exec/%.c 
	@mkdir -p obj/exec
	$(CC) $(CFLAGS) -c $< -o $@

obj/parse/%.o: parse/%.c 
	@mkdir -p obj/parse
	$(CC) $(CFLAGS) $(INCLUDES) -g -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(RM) ./obj
	$(RM) libft/*.o

fclean: clean
	$(RM) $(NAME)
	$(RM) libft/libft.a

re: fclean all

.PHONY: clean fclean re all
