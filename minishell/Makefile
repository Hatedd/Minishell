NAME = minishell

SRCS =  main.c \
		execution/exec_main.c \
		execution/exec_utils.c \
		execution/exec_utils1.c \
		execution/exec_utils2.c \
		execution/exec_utils3.c \
		execution/exec_utils4.c \
		execution/bult_in/export_utils.c \
		execution/bult_in/bult_in.c \
		execution/bult_in/export_utils2.c \
		execution/bult_in/export_utils3.c \
		execution/bult_in/export.c\
		execution/bult_in/ft_pwd.c\
		execution/bult_in/ft_cd.c\
		execution/bult_in/ft_echo.c\
		execution/bult_in/ft_env.c\
		execution/bult_in/ft_unset.c\
		execution/bult_in/ft_exit.c\
		parsing/lexer.c \
		parsing/doubly_lst.c \
		parsing/heredoc.c \
		parsing/meta.c \
		parsing/ft_hexpand.c \
		parsing/ft_utils.c\
		parsing/ft_expand.c \
		parsing/ft_ambrd_split.c \
		parsing/ft_error.c \
		parsing/ft_parser.c \
		parsing/ft_redirection.c \
		parsing/ft_utils2.c parsing/heredoc_help.c \
		parsing/main_utils.c

OBJS = $(SRCS:.c=.o)

CC = @cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -I /Users/$(USER)/.brew/opt/readline/include #-g3 -fsanitize=address


all : 	${NAME}

${NAME} : ${OBJS}
		@stty -echoctl
		@make -C libft/
		${CC} ${CFLAGS} libft/libft.a -L /Users/$(USER)/.brew/opt/readline/lib -l readline ${OBJS} -o ${NAME}

clean :
	@make clean -C libft/
	@${RM} ${OBJS}

fclean : clean
	@make fclean -C libft/
	@${RM} ${NAME}

re : fclean all

.PHONY: all clean fclean re
