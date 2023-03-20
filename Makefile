NAME = pipex

CC = @cc

CFLAGS = -Wall -Wextra -Werror -g

RM = @rm -f

LIBFT = Libft/libft/libft.a
LIBFT_PATH = Libft/libft

$(LIBFT): $(shell make -C $(LIBFT_PATH) -q libft.a)
		make -C $(LIBFT_PATH)


SRC = pipex.c process.c commands.c

OBJ = $(SRC:.c=.o)
 
$(NAME):		$(OBJ) $(LIBFT)
				$(CC) $(OBJ) $(LIBFT) 

all:			$(NAME)

clean:
				$(RM) $(OBJ)
				make clean -C $(LIBFT_PATH)

fclean: 		clean
				$(RM) $(NAME)
				make clean -C $(LIBFT_PATH)

re:		fclean	$(NAME)