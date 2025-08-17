NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O3 -I/usr/include -Imlx_linux

SRC = main.c destroy_error.c
OBJ = $(patsubst %.c,obj/%.o,$(SRC))

LIBFT = libft/libft.a
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME) $(LIBFT)

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

obj/parse/%.o: src/parse/%.c 
	@mkdir -p obj/parse
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(RM) ./obj
	$(RM) libft/*.o

fclean: clean
	$(RM) $(NAME)
	$(RM) libft/libft.a

re: fclean all

.PHONY: clean fclean re all
