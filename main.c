/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:08:19 by chabrune          #+#    #+#             */
/*   Updated: 2023/02/22 17:36:23 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int fd1, int fd2, char **argv, char **envp)
{
	int pid;
	int fd[2];
	pipe(fd);
	pid = fork();
	if(pid == - 1)
		return(1);
	else if(pid == 0)
		child_process(fd1, fd, envp, argv);
	else
		parent_process(fd2,fd, envp, argv);
}

int	child_process(int fd1, int *fd, char **envp, char **argv)
{
	if(dup2(fd1, STDIN_FILENO) == -1)
		return(2);
	if(dup2(fd[1], STDOUT_FILENO) == -1)
		return(3);
	close(fd[1]);
	close(fd1);
	hello(envp, argv, 2);
	return(0);
}

int	parent_process(int fd2, int *fd, char **envp, char **argv)
{
	int status;
	waitpid(-1, &status, 0);
	if(dup2(fd2, STDOUT_FILENO) == -1)
		return(4);
	if(dup2(fd[0], STDIN_FILENO) == -1)
		return(5);
	close(fd[0]);
	close(fd2);
	hello(envp, argv, 3);
	return(0);
}

char	*find_path(char **envp)
{
	int i;

	i = -1;
	while(envp[++i])
	{
		if(strncmp(envp[i], "PATH", 4) == 0)
			return(envp[i]);
	}
	return(0);
}

int	hello(char **envp, char **argv, int ar)
{
	char *pathenv;
	char **mypath;
	char **cmdargs;
	int i;

	i = -1;
	cmdargs = ft_split(argv[ar], ' ');
	pathenv = find_path(envp);
	mypath = ft_split(pathenv, ':');
	while(mypath[++i])
	{
		char *cmd = ft_strjoin(mypath[i], argv[2]);
		execve(cmd, cmdargs, envp);
	    free(cmd);
	}
	return (EXIT_FAILURE);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	int fd1;
	int fd2;

	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644); // Create a file if it doesnt exit -- TRUNC == reset file a 0
	if(fd1 < 0 || fd2 < 0)
		return(1);
	pipex(fd1, fd2, argv, envp);
	return(0);
}
