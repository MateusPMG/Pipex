/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:54:45 by mpatrao           #+#    #+#             */
/*   Updated: 2023/04/04 14:50:03 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (ac != 5)
		return (write(1, "Error, must be 4 arguments only.\n", 33));
	if (pipe(fd) == -1)
	{
		perror("Error");
		exit(1);
	}
	pid = fork();
	if (pid == 0)
		child(fd, av, envp);
	waitpid(pid, NULL, 0);
	parent(fd, av, envp);
	return (0);
}
