NAME = philo
C = gcc
FLAGS = -Wall -Wextra -Werror -pthread -O2
# SANITIZE = -fsanitize=thread

BIN = ./bin/

SRC = main.c utils.c parsing.c init.c routine.c philo.c
OBJ = $(addprefix $(BIN), $(SRC:%.c=%.o))

all: $(NAME)

$(NAME): $(BIN) $(OBJ)
	$(C) $(FLAGS) $(SANITIZE) -o $(NAME) $(OBJ)

$(BIN)%.o: %.c
	$(C) $(FLAGS) $(SANITIZE) -o $@ -c $<

$(BIN):
	mkdir -p -m 700 $(BIN)

clean:
	rm -rf *.dSYM
	rm -f $(BIN)*.o

fclean: clean
	rm -rf $(NAME)
	rm -rf $(BIN)

valgrind:
	make && valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

re: fclean all

.PHONY: all clean fclean valgrind re