/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:44:06 by mpatrao           #+#    #+#             */
/*   Updated: 2023/03/20 14:22:02 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(int *fd, char **av, char **envp)
{
	int	infile_fd;

	close(fd[0]);
	infile_fd = open(av[1], O_RDONLY, 0777);
	if (infile_fd < 0)
	{
		perror("Error");
		exit(1);
	}
	dup2(infile_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	use_command(av[2], envp);
	close(fd[1]);
}

void	parent(int *fd, char **av, char **envp)
{
	int	outfile_fd;

	close(fd[1]);
	outfile_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd < 0)
	{
		perror("Error");
		exit(1);
	}
	dup2(outfile_fd, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	use_command(av[3], envp);
	close(fd[0]);
}
