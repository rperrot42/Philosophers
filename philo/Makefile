DIR_OBJS = .objs

SRC = main.c \
	print_error.c \
	atoi.c \
	read_args.c \
	create_philo.c \
	init_time.c \
	philo_action.c

CC = cc

FLAGS = -Werror -Wextra -Wall -pthread -g3

OBJS = $(addprefix $(DIR_OBJS)/, $(SRC:.c=.o))

INCLUDE = philo.h

NAME = philo

$(DIR_OBJS)/%.o: %.c Makefile $(INCLUDE) | $(DIR_OBJS)
	$(CC) $(FLAGS) -c $< -o $@

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(DIR_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all