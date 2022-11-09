FLAGS		= -Wall -Wextra -Werror
NAME		= philo
SRCS		= data_philo.c main.c utils.c thread.c init.c

OBJS		= ${SRCS:c=o}

RM			= rm -f

HEAD		= philo.h

.PHONY:		all clean fclean re

all:		${NAME}

${NAME}:	${OBJS} ${HEAD} Makefile 
			${CC} ${FLAGS} ${OBJS} -o ${NAME}

%.o:		%.c ${HEAD}
			${CC} ${FLAGS} -c $< -o $@

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME} 

re:			fclean all