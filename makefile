NAME = philo
CC = gcc
SRC = main.c utils.c init.c
CFLAGS = -Wextra -Wall -Werror -fsanitize=thread
OBJ = ${SRC:.c=.o}

GREEN = \x1b[32m
RESET = \033[0m
RED   = \x1b[31m

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)Compiling...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Done!$(RESET)"

clean:
	@echo "$(RED)Cleaning...$(RESET)"
	@rm -f $(OBJ)
	@echo "$(RED)Done!$(RESET)"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean, all, fclean, re