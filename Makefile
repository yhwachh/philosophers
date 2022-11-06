SRCS		= data_philo.c atoi.c main.c init_ad_thrds.c utils.c

OBJS		= ${SRCS:c=o}

NAME		= philo

FLAGS		= -Wall -Wextra -Werror

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