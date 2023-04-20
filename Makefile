NAME = pipex

CC = @cc

CFLAGS = -Wall -Wextra -Werror -g -o pipex -fsanitize=address

RM = @rm -f

SRC = pipex.c process.c commands.c

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a
LIBFT_PATH = libft/

$(LIBFT): $(shell make -C $(LIBFT_PATH) -q libft.a)
		make -C $(LIBFT_PATH)

$(NAME):		$(OBJ) $(LIBFT)
				$(CC) $(CFLAGS) $(OBJ) $(LIBFT) 

all:			$(NAME)

clean:
				make clean -C $(LIBFT_PATH)
				$(RM) $(OBJ)

fclean: 		clean
				make fclean -C $(LIBFT_PATH)
				$(RM) $(NAME)

re:		fclean	$(NAME)

.PHONY: all clean fclean re