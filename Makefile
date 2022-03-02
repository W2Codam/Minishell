# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: w2wizard <w2wizard@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/02 18:01:17 by w2wizard      #+#    #+#                  #
#    Updated: 2022/03/02 21:07:39 by pvan-dij      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


# //= Variables =// #

NAME 	= minishell
CFLAGS	= -g -Wall -Wextra -Werror -Wunreachable-code 

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
SRCS	=	./src/internal/cd.c 		\
./src/internal/echo.c 					\
./src/internal/env.c 					\
./src/internal/exit.c 					\
./src/internal/export.c 				\
./src/internal/ft_builtin_utils.c 		\
./src/internal/pwd.c 					\
./src/internal/unset.c 					\
./src/main.c 							\
./src/parser/ft_builtincheck.c 			\
./src/parser/ft_lexer.c 				\
./src/parser/ft_parser.c 				\
./src/parser/heredoc.c 					\
./src/parser/splitting.c 				\
./src/parser/stringexpand.c 			\
./src/parser/temp/get_next_line.c 		\
./src/parser/temp/get_next_line_utils.c \
./src/shell.c 							\
./src/utils/parser_utils.c 				\
./src/utils/shell_utils.c 				\
./src/utils/stringexpand_utils.c 		\
./src/utils/unix_env_utils.c 			\
./src/utils/unix_env_utils_utils.c 		\
./src/utils/unix_err_utils.c 			\
./src/utils/unix_file_utils.c 			\
./src/utils/unix_utils.c 				\
./src/utils/utils.c 					
			
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