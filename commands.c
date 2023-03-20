/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:18:17 by mpatrao           #+#    #+#             */
/*   Updated: 2023/03/20 16:09:51 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	cmd_args = ft_split(str, 32);
	cmd = get_cmd(cmd_paths, cmd_args[0]);
	if (!cmd)
	{
		free(cmd_paths);
		free(cmd_args);
		free(cmd);
		perror("Error");
		exit (1);
	}
	execve(cmd, cmd_args, envp);
}
