CC=cc
FLAGS=-Wall -Werror -Wextra
NAME=try
OBJ=complex_maker.c

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -f try
	
re: clean all

.PHONY: all clean re
