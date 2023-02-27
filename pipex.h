#ifndef PIPEX_H
# define PIPEX_H

# include "/Users/chabrune/Desktop/42-school/ft_printf/ft_printf.h"
# include "/Users/chabrune/Desktop/42-school/libft/libft.h"

typedef struct s_allyouneed
{
	char **env;
	char **ar;
	int tube[2];
	char **cmd_paths;
	char *paths;
	char **cmd_args;
	char *cmd;
	int pid1;
	int pid2;
	int fdin;
	int fdout;
}	t_allyouneed;

int	    child1_process(t_allyouneed *ola);
char 	*get_cmd(char **cmd_paths, char *cmd);
void 	pipex(t_allyouneed *ola);
void	parent_process(t_allyouneed *ola);
int	    child2_process(t_allyouneed *ola);
int 	hello(t_allyouneed *ola, char *cmd);

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>


#endif