/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:06:57 by mpatrao           #+#    #+#             */
/*   Updated: 2023/03/23 15:00:57 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

void	child(int *fd, char **av, char **envp);
void	parent(int *fd, char **av, char **envp);
void	use_command(char *str, char **envp);

#endif