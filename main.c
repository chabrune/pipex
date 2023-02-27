/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:08:19 by chabrune          #+#    #+#             */
/*   Updated: 2023/02/27 20:37:54 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_allyouneed *ola)
{
	if(pipe(ola->tube) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	ola->pid1 = fork();
	if(ola->pid1 == - 1)
	{
		perror("fork");
        exit(EXIT_FAILURE);
	}
	else if(ola->pid1 == 0)
		child1_process(ola);
	else
	{
		ola->pid2 = fork();
		if(ola->pid2 == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if(ola->pid2 == 0)
			child2_process(ola);
		else
			parent_process(ola);
	}
}

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
	if(dup2(ola->fdin, STDIN_FILENO) == -1)
	{
            perror("dup2");
            exit(EXIT_FAILURE);
    }
	if(dup2(ola->tube[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(ola->tube[0]);
	ola->cmd_args = ft_split(ola->ar[2], ' ');
	ola->cmd = get_cmd(ola->cmd_paths, ola->cmd_args[0]);
	execve(ola->cmd, ola->cmd_args, ola->env);
	perror("exceve");
	exit(EXIT_FAILURE);
	return(0);
}

int	child2_process(t_allyouneed *ola)
{
	if(dup2(ola->fdout, STDOUT_FILENO) == -1)
	{
            perror("dup2");
            exit(EXIT_FAILURE);
    }
	if(dup2(ola->tube[0], STDIN_FILENO) == -1)
	{
            perror("dup2");
            exit(EXIT_FAILURE);
    }
	close(ola->tube[1]);
	ola->cmd_args = ft_split(ola->ar[3], ' ');
	ola->cmd = get_cmd(ola->cmd_paths, ola->cmd_args[0]);
	execve(ola->cmd, ola->cmd_args, ola->env);
	perror("execve");
	exit(EXIT_FAILURE);
	return(0);
}

char	*find_path(char **env)
{
	int i;

	i = -1;
	while(strncmp("PATH", *env, 4))
		env++;
	return(*env + 5);
}

char *get_cmd(char **paths, char *cmd)
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

void	close_fd(t_allyouneed *ola)
{
	close(ola->tube[0]);
	close(ola->tube[1]);
}

int	get_all_you_need(char **ar, char **env, t_allyouneed *ola)
{
	ola->ar = ar;
	ola->env = env;
	ola->paths = find_path(env);
	ola->cmd_paths = ft_split(ola->paths, ':');
	ola->fdin = open(ar[1], O_RDONLY);
	if(ola->fdin == -1)
	{
		perror("open");
        exit(EXIT_FAILURE);
	}
	ola->fdout = open(ar[4], O_CREAT | O_RDWR | O_TRUNC, 0644); // Create a file if it doesnt exit -- TRUNC == reset file a 0
	if(ola->fdout == -1)
	{
		perror("open");
        exit(EXIT_FAILURE);
	}
	return(0);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	t_allyouneed ola;
	get_all_you_need(argv, envp, &ola);
	pipex(&ola);
	return(0);
}
