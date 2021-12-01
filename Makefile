# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lde-la-h <lde-la-h@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/30 13:24:16 by lde-la-h      #+#    #+#                  #
#    Updated: 2021/11/30 14:59:28 by lde-la-h      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# //= Variables =// #

NAME 	= minishell
CFLAGS	= -Wextra -Werror -Wall -Wunreachable-code -O3

# //= Colors =// #
BOLD	= \e[1m
GREEN	= \x1b[32m
RESET	= \033[0m
RED		= \x1b[31m

# Define the header location
HEADERS = -I ./libs/libft

# //= Files =// #

# TODO: Add files, remove shell command.
SRCS	=	$(shell find ./src -iname "*.c")
			
OBJS	= ${SRCS:.c=.o}

# //= Rules =// #
## //= Compile =// #
all: $(NAME)

%.o: %.c
	@printf	"$(GREEN)$(BOLD)\rCompiling: $(notdir $<) 🔨$(RESET)"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) -o $@
	@echo "$(GREEN)Done ✅$(RESET)"

## //= Commands =// #

# Clean
clean:
	@echo "$(RED)Cleaning 🧹$(RESET)"
	@rm -f $(OBJS)

# Full clean
fclean: clean
	@rm -f $(NAME)

# Re-compile
re:	fclean all

## //= Misc =// #

# Phonies as not to confuse make, these are actual commands, not files.
.PHONY: all, clean, fclean, re