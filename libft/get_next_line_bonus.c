/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:35:53 by mpatrao           #+#    #+#             */
/*   Updated: 2023/04/28 12:00:26 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	int			read_n;
	char		*full_line;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > FOPEN_MAX)
		return (NULL);
	full_line = ft_allocate_join(0, buffer[fd]);
	if (ft_reset_buffer(buffer[fd]))
		return (full_line);
	read_n = read(fd, buffer[fd], BUFFER_SIZE);
	if (read_n < 0 || (read_n == 0 && (*full_line == '\0')))
		return (ft_freeline(full_line));
	while (read_n > 0)
	{
		full_line = ft_allocate_join(full_line, buffer[fd]);
		if (ft_reset_buffer(buffer[fd]))
			break ;
		read_n = read(fd, buffer[fd], BUFFER_SIZE);
	}
	if (read_n < 0)
	{
		return (ft_freeline(full_line));
	}
	return (full_line);
}
