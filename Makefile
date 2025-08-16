NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O3 -I/usr/include -Imlx_linux

SRC = main.c
OBJ = $(patsubst %.c,obj/%.o,$(SRC))

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

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

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
