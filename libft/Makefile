NAME	=		libft.a

CC		=		cc

CFLAGS	=		-Wall -Wextra -Werror

RM		=		rm -f

SRC 	=	 ft_strlen.c ft_strlcpy.c ft_strlcat.c\
ft_strnstr.c ft_strncmp.c ft_memcpy.c\
ft_strdup.c ft_substr.c ft_strjoin.c \
ft_split.c get_next_line_bonus.c get_next_line_utils_bonus.c


OBJ		=		$(SRC:.c=.o)


all:			$(NAME)

$(NAME):		$(OBJ)
		ar rcs	$(NAME) $(OBJ)

clean:
				$(RM) $(OBJ) 
fclean: clean
				$(RM) $(NAME)

re:		fclean	$(NAME)
