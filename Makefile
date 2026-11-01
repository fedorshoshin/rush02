NAME	= rush
CC	= cc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= main.c file_io.c keys.c  validate.c construct.c dict.c print_group.c utils.c 
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c rush02.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


