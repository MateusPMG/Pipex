NAME = pipex
LIBFT = libft/libft.a
LIBFT_PATH = libft/
SRC = pipex.c process.c commands.c
RM = @rm -f
CC = @cc
CFLAGS = -Wall -Wextra -Werror -g -o pipex -fsanitize=address

OBJ = $(SRC:.c=.o)

$(NAME):		$(OBJ)	
				@$(MAKE) --no-print-directory -C $(LIBFT_PATH)
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