# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lde-la-h <lde-la-h@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/30 13:24:16 by lde-la-h      #+#    #+#                  #
#    Updated: 2021/12/01 14:51:45 by lde-la-h      ########   odam.nl          #
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
HEADERS = -I ./libs/libft -I ./include -I ~/.brew/opt/readline/include
ARCHIVES = ./libs/libft/libft.a -lreadline -L ~/.brew/opt/readline/lib 

# //= Files =// #

# TODO: Add files, remove shell command.
SRCS	=	$(shell find ./src -iname "*.c")
			
OBJS	= ${SRCS:.c=.o}

# //= Rules =// #
## //= Compile =// #
all: libft $(NAME)

%.o: %.c
	@printf	"$(GREEN)$(BOLD)\rCompiling: $(notdir $<) 🔨$(RESET)"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) 

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) $(ARCHIVES) -o $(NAME) 
	@echo "$(GREEN)Done ✅$(RESET)"

libft:
	@$(MAKE) -C libs/libft

## //= Commands =// #

# Clean
clean:
	@echo "$(RED)Cleaning 🧹$(RESET)"
	@$(MAKE) -C libs/libft clean
	@rm -f $(OBJS)

# Full clean
fclean: clean
	@rm -f $(NAME)
	@rm -f ./libs/libft/libft.a

# Re-compile
re:	fclean all

## //= Misc =// #

# Phonies as not to confuse make, these are actual commands, not files.
.PHONY: all, clean, fclean, re