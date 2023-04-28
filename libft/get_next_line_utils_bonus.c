/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:36:42 by mpatrao           #+#    #+#             */
/*   Updated: 2023/04/28 12:00:35 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_checklen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	if (s && s[i] == '\n')
		i++;
	return (i);
}

char	*ft_allocate_join(char *fl, char *bf)
{
	char	*p;
	int		i;
	int		j;

	p = (char *)malloc(sizeof(char) * (ft_checklen(fl) + ft_checklen(bf) + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (fl && fl[i])
	{
		p[i] = fl[i];
		i++;
	}
	j = 0;
	while (bf[j] && bf[j] != '\n')
		p[i++] = bf[j++];
	if (bf[j] == '\n')
		p[i++] = bf[j];
	p[i] = '\0';
	if (fl)
		free (fl);
	return (p);
}

char	*ft_freeline(char *fl)
{
	free(fl);
	return (NULL);
}

int	ft_reset_buffer(char *buffer)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (buffer && buffer[i])
	{
		if (flag == 1)
			buffer[j++] = buffer[i];
		if (buffer[i] == '\n')
			flag = 1;
		buffer[i] = 0;
		i++;
	}
	return (flag);
}
