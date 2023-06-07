SRCS = philosophers.c \
	./src/checkers.c \
	./src/utils.c \
	./src/init.c \
	./src/clean.c \
	./src/threads.c \
	./src/philos.c

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