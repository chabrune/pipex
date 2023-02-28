#ifndef PIPEX_H
# define PIPEX_H

# include "/home/chabrune/ft_printf/ft_printf.h"
# include "/home/chabrune/libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_allyouneed
{
	char	**env;
	char	**ar;
	int		tube[2];
	char	**cmd_paths;
	char	*paths;
	char	**cmd_args;
	char	*cmd;
	int		pid1;
	int		pid2;
	int		fdin;
	int		fdout;
}			t_allyouneed;

int			error_msg(char *error);
int			error_and_exit(char *error);
void		free_parent(t_allyouneed *ola);
void		free_child(t_allyouneed *ola);
int			child1_process(t_allyouneed *ola);
char		*get_cmd(char **cmd_paths, char *cmd);
void		pipex(t_allyouneed *ola);
void		parent_process(t_allyouneed *ola);
int			child2_process(t_allyouneed *ola);
int			hello(t_allyouneed *ola, char *cmd);

#endif