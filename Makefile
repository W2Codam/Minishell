# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: w2wizard <w2wizard@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/02 18:01:17 by w2wizard      #+#    #+#                  #
#    Updated: 2022/02/24 20:27:36 by lde-la-h      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


# //= Variables =// #

NAME 	= minishell
CFLAGS	= #-Wall -Wextra -Werror -Wunreachable-code 

# //= Colors =// #
BOLD	= \033[1m
BLACK	= \033[30;1m
RED		= \033[31;1m
GREEN	= \033[32;1m
YELLOW	= \033[33;1m
BLUE	= \033[34;1m
MAGENTA	= \033[35;1m
CYAN	= \033[36;1m
WHITE	= \033[37;1m
RESET	= \033[0m

# Define the header location
HEADERS = -I ./libs/libft  -I ./include -I ~/.brew/opt/readline/include
ARCHIVES = ./libs/libft/libft.a -lreadline -L ~/.brew/opt/readline/lib 

# //= Files =// #

# TODO: Add files, remove shell command.
SRCS	=	$(shell find ./src -iname "*.c")
			
OBJS	= ${SRCS:.c=.o}

# //= Rules =// #
## //= Compile =// #
all: libft $(NAME)
	
%.o: %.c
	@printf	"$(GREEN)$(BOLD)\rCompiling: $(notdir $<) 🔨 $(RESET)"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) 

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) $(ARCHIVES) -o $(NAME)
	@echo "$(GREEN)Done ✅$(RESET)"
libft:
	@$(MAKE) -C libs/libft
mongol: all
	@open https://youtu.be/6WlI24rv__g?t=27
	@osascript -e "set Volume 5"

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