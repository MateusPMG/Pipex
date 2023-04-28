/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:56:07 by mpatrao           #+#    #+#             */
/*   Updated: 2023/04/28 16:42:21 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	open_file(int ac, char **av, t_files *file)
{
	file->fdin = open(av[1], O_RDONLY);
	file->fdout = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file->fdout < 0)
	{
		perror("Error");
		exit(1);
	}
	dup2(file->fdin, STDIN_FILENO);
}

void	here_doc(int ac, char **av, t_files *file)
{
	char	*buf;

	file->fdin = open(".here_doc", O_RDWR | O_CREAT | O_TRUNC | 0644);
	file->fdout = open(av[ac - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	file->here = 1;
	if (file->fdin == -1)
	{
		perror("Error");
		exit(1);
	}
	while (1)
	{
		write(1, "here_doc>", 9);
		buf = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(buf, av[2], ft_strlen(av[2]))
			&& buf[ft_strlen(av[2])] == '\n')
			break ;
		write(file->fdin, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
}

void	redirect(char *cmd, char**env, int fdin)
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
		if (fdin == STDIN_FILENO)
			exit(1);
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

	i = 3;
	file.fdin = 0;
	file.fdout = 0;
	file.here = 0;
	if (ac < 5)
		return (write(1, "Error, must be at least 4 arguments.\n", 37));
	else
	{
		if (!ft_strncmp("here_doc", av[1], ft_strlen(av[1])))
			here_doc(ac, av, &file);
		else
			open_file(ac, av, &file);
		dup2(file.fdin, STDIN_FILENO);
		redirect(av[2 + file.here], env, file.fdin);
		while (i < ac - 2 + file.here)
			redirect(av[i++], env, 1);
		dup2(file.fdout, STDOUT_FILENO);
		use_command(av[ac - 2], env);
	}
	return (1);
}
