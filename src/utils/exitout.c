#include "minishell.h"

void	exitout(char *s)
{
	if (s == NULL)
		write(1, "\x1b[A\x1b[15Cexit\n", 13);
	else
		write(1, "exit\n", 5);
}