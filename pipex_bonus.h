/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:06:57 by mpatrao           #+#    #+#             */
/*   Updated: 2023/04/28 15:49:53 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"

/*for pid_t, waitpid*/
# include <sys/types.h>
# include <sys/wait.h>

/*for exit, free, malloc*/
# include <stdlib.h>

/*for perror, open, link*/
# include <stdio.h>

/*for close*/
# include <unistd.h>

/*for file control options and flags*/
# include <fcntl.h>

typedef struct files
{
	int	fdin;
	int	fdout;
	int	here;
}					t_files;

void	use_command(char *str, char **envp);
void	free_all(char **args, char **paths, char *cmd);

#endif