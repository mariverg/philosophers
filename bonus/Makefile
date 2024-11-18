NAME = philo_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -pthread

SRCS = main.c \
	   init.c \
	   routine.c \
	   utils.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c philosophers_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re