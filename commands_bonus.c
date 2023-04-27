/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:18:17 by mpatrao           #+#    #+#             */
/*   Updated: 2023/04/27 14:38:28 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*ft_strrchr(const char *s, int c)
{
	char	*p;

	p = (char *)s;
	while (*s)
		s++;
	if (c == '\0')
		return ((char *)s);
	while (s >= p)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s--;
	}
	return (NULL);
}

static int	is_path(char *str, char **path)
{
	int	i;

	i = 0;
	if (*str == '/')
	{
		while (path[i])
		{
			if (ft_strncmp(str, path[i], ft_strlen(path[i])) == 0)
				return (1);
			i++;
		}
	}
	return (0);
}

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
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

void	use_command(char *str, char **envp)
{
	char	*path;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;

	path = find_path(envp);
	cmd_paths = ft_split(path, ':');
	if (is_path(str, cmd_paths))
		str = ft_strrchr(str, '/');
	cmd_args = ft_split(str, 32);
	cmd = get_cmd(cmd_paths, cmd_args[0]);
	if (!cmd)
	{
		free_all(cmd_args, cmd_paths, cmd);
		perror("Error1");
		exit (1);
	}
	if (execve(cmd, cmd_args, envp) == -1)
	{
		free_all(cmd_args, cmd_paths, cmd);
		perror("Error2");
		exit (1);
	}
}
