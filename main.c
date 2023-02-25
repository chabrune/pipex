/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:08:19 by chabrune          #+#    #+#             */
/*   Updated: 2023/02/25 21:13:38 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_allyouneed *ola)
{
	pipe(ola->fdraw);
	ola->pid = fork();
	if(ola->pid == - 1)
		return;
	else if(ola->pid == 0)
		child_process(ola);
	else
		parent_process(ola);
}

int	child_process(t_allyouneed *ola)
{
	if(dup2(ola->fdin, STDIN_FILENO) == -1)
		return(2);
	if(dup2(ola->fdraw[1], STDOUT_FILENO) == -1)
		return(3);
	close(ola->fdin);
	close(ola->fdraw[0]);
	return(0);
}

int	parent_process(t_allyouneed *ola)
{
	wait(NULL);
	if(dup2(ola->fdout, STDOUT_FILENO) == -1)
		return(4);
	if(dup2(ola->fdraw[0], STDIN_FILENO) == -1)
		return(5);
	close(ola->fdraw[1]);
	close(ola->fdout);
	hello(ola);
	return(0);
}

char	*find_path(t_allyouneed *ola)
{
	int i;

	i = -1;
	while(ola->env[++i])
	{
		if(strncmp(ola->env[i], "PATH", 5 ) == 0)
			return(ola->env[i]);
	}
	return(0);
}

int	hello(t_allyouneed *ola)
{
	char *pathenv;
	char **mypath;
	char **cmdargs;
	int i;

	i = -1;
	cmdargs = ft_split(ola->ar[2], ' ');
	pathenv = find_path(ola);
	mypath = ft_split(pathenv, ':');
	while(mypath[++i])
	{
		char *cmd = ft_strjoin(mypath[i], ola->ar[2]);
		execve(cmd, cmdargs, ola->env);
	    free(cmd);
	}
	return (EXIT_FAILURE);
}

int	get_all_you_need(char **ar, char **env, t_allyouneed *ola)
{
	ar = ola->ar;
	env = ola->env;
	ola->fdin = open(ar[1], O_RDONLY);
	ola->fdout = open(ar[4], O_CREAT | O_RDWR | O_TRUNC, 0644); // Create a file if it doesnt exit -- TRUNC == reset file a 0
	if(ola->fdin < 0 || ola->fdout < 0)
		return(1);
	return(0);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	t_allyouneed *ola;
	ola = NULL;
	ola = malloc(sizeof(ola));
	get_all_you_need(argv, envp, ola);
	pipex(ola);
	return(0);
}
