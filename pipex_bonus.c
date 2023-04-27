/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:56:07 by mpatrao           #+#    #+#             */
/*   Updated: 2023/04/27 14:55:18 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	redirect(char *cmd, char**env)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("Error");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		use_command(cmd, env);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

int	main(int ac, char **av, char **env)
{
	int	fdin;
	int	fdout;
	int	i;

	i = 2;
	if (ac < 5)
		return (write(1, "Error, must be at least 4 arguments.\n", 37));
	else
	{
		fdin = open(av[1], O_RDONLY);
		fdout = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fdout < 0 || fdin < 0)
		{
			perror("Error");
			exit(1);
		}
		dup2(fdin, STDIN_FILENO);
		redirect(av[2], env);
		while (i <= ac - 2)
			redirect(av[i++], env);
		dup2(fdout, STDOUT_FILENO);
		use_command(av[ac - 2], env);
	}
	return (1);
}
