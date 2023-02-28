#include "pipex.h"

void	free_parent(t_allyouneed *ola)
{
	int	i;

	i = -1;
	while (ola->cmd_paths[++i])
		free(ola->cmd_paths[i]);
	free(ola->cmd_paths);
}

void	free_child(t_allyouneed *ola)
{
	int	i;

	i = -1;
	while (ola->cmd_args[++i])
		free(ola->cmd_args[i]);
	free(ola->cmd_args);
}

int	error_msg(char *error)
{
	write(2, error, ft_strlen(error));
	return (1);
}

int	error_and_exit(char *error)
{
	perror(error);
	exit(1);
}