NAME = minishell

SRC = main.c lexer.c doubly_lst.c

OBJS = ${SRC:.c=.o}

CC = CC

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -I /Users/${USER}/readline/include -g -fsanitize=address

all : 	${NAME}

${NAME} : ${OBJS}
#		${CC} ${CFLAGS} -L /Users/${USER}/readline/lib ${OBJS} -o ${NAME}
		${CC} ${CFLAGS} -lreadline libft/libft.a ${OBJS} -o ${NAME}

clean :
	@${RM} ${OBJS}

fclean : clean
	@${RM} ${NAME}

re : fclean all

.PHONY: all clean fclean re