/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:56:07 by mpatrao           #+#    #+#             */
/*   Updated: 2023/05/03 11:58:48 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	write_to_pipe(int *fd, char **av)
{
	char	*buf;

	while (1)
	{
		write(1, "here_doc>", 9);
		buf = get_next_line(STDIN_FILENO);
		if (!buf || (!ft_strncmp(buf, av[2], ft_strlen(av[2]))
				&& buf[ft_strlen(av[2])] == '\n'))
			break ;
		write(*fd, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close(*fd);
}

int	here_doc(char **av)
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
		write_to_pipe(&pipefd[1], av);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	return (STDIN_FILENO);
}

int	start_files(int ac, char **av, t_files *file)
{
	int	i;

	if (!ft_strncmp(av[1], "here_doc", 8))
	{
		i = 3;
		file->fdin = here_doc(av);
		file->fdout = open(av[ac - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		i = 2;
		file->fdin = open(av[1], O_RDONLY);
		file->fdout = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	return (i);
}





void	redirect(char *cmd, char **env)
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
	int		i;
	t_files	file;

	file.fdin = 0;
	file.fdout = 0;
	file.here = 0;
	if (ac < 5)
		return (write(1, "Error, must be at least 4 arguments.\n", 37));
	else
	{
		i = start_files(ac, av, &file);
		dup2(file.fdin, STDIN_FILENO);
		dup2(file.fdout, STDOUT_FILENO);
		while (i < ac - 2)
		{
			redirect(av[i], env);
			i++;
		}
		use_command(av[i], env);
	}
	return (1);
}
