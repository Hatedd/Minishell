NAME = minishell

SRC = main.c lexer.c doubly_lst.c heredoc.c meta.c ft_hexpand.c ft_utils.c ft_expand.c ft_ambrd_split.c

OBJS = ${SRC:.c=.o}

CC = CC

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -I /Users/${USER}/readline/include -g -fsanitize=address

all : 	${NAME}

${NAME} : ${OBJS}
		stty -echoctl
		${CC} ${CFLAGS} libft/libft.a -L/Users/${USER}/readline/lib -lhistory -L/Users/${USER}/readline/lib -lreadline ${OBJS} -o ${NAME}
		# ${CC} ${CFLAGS} -lreadline libft/libft.a ${OBJS} -o ${NAME}

clean :
	@${RM} ${OBJS}

fclean : clean
	@${RM} ${NAME}

re : fclean all

.PHONY: all clean fclean re