#include "pipex.h"

void	pipex(t_allyouneed *ola)
{
	if (pipe(ola->tube) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	ola->pid1 = fork();
	if (ola->pid1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (ola->pid1 == 0)
		child1_process(ola);
	else
	{
		ola->pid2 = fork();
		if (ola->pid2 == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (ola->pid2 == 0)
			child2_process(ola);
		else
			parent_process(ola);
	}
}


char	*find_path(char **env)
{
	while (strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

int	get_all_you_need(char **ar, char **env, t_allyouneed *ola)
{
	ola->ar = ar;
	ola->env = env;
	ola->paths = find_path(env);
	ola->cmd_paths = ft_split(ola->paths, ':');
	ola->fdin = open(ar[1], O_RDONLY);
	if (ola->fdin == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	ola->fdout = open(ar[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (ola->fdout == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	if(argc == 5)
	{
		t_allyouneed ola;
		get_all_you_need(argv, envp, &ola);
		pipex(&ola);
		free_parent(&ola);
	}
	else
		return(error_msg("ERR_INPUT"));
	return (0);
}