NAME = pipex

CC = cc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

SRCS = 	pipex.c\
		utils.c\
		libft/libft.a\

$(NAME) :
	make all -C libft
	gcc $(CFLAGS) $(SRCS) -o $(NAME)


all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

clean :
	$(RM)
	make clean -C libft

re : fclean all