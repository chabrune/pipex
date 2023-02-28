#include "pipex.h"

void	parent_process(t_allyouneed *ola)
{
	close(ola->fdin);
	close(ola->fdout);
	close(ola->tube[0]);
	close(ola->tube[1]);
	waitpid(ola->pid1, NULL, 0);
	waitpid(ola->pid2, NULL, 0);
}

int	child1_process(t_allyouneed *ola)
{
	if (dup2(ola->fdin, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (dup2(ola->tube[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(ola->tube[0]);
	ola->cmd_args = ft_split(ola->ar[2], ' ');
	ola->cmd = get_cmd(ola->cmd_paths, ola->cmd_args[0]);
	execve(ola->cmd, ola->cmd_args, ola->env);
	free_child(ola);
	perror("exceve");
	exit(EXIT_FAILURE);
	return (0);
}

int	child2_process(t_allyouneed *ola)
{
	if (dup2(ola->fdout, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (dup2(ola->tube[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(ola->tube[1]);
	ola->cmd_args = ft_split(ola->ar[3], ' ');
	ola->cmd = get_cmd(ola->cmd_paths, ola->cmd_args[0]);
	execve(ola->cmd, ola->cmd_args, ola->env);
	free_child(ola);
	perror("execve");
	exit(EXIT_FAILURE);
	return (0);
}