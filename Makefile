SRCS = philosophers.c \
	./src/checkers.c \
	./src/clean.c \
	./src/init.c \
	./src/philo_one.c \
	./src/philos_even.c \
	./src/philos_uneven.c \
	./src/philos_utils.c \
	./src/threads.c \
	./src/utils.c \

OBJS = ${SRCS:.c=.o}

NAME = philo

HEADER = include

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I$(HEADER)

RM = rm -f

all:	$(NAME)

#.c.o:
#	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

#.c.o:
#	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

.PHONY:	clean fclean re

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all