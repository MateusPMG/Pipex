/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:17:17 by mpatrao           #+#    #+#             */
/*   Updated: 2022/11/16 15:23:18 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	stringcount(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			i++;
			s++;
		}
		while (*s && *s != c)
			s++;
	}
	return (i);
}

void	allocate(char **array, char const *s, char c)
{
	char const	*previous;
	char		**temparray;

	temparray = array;
	while (*s)
	{
		while (*s == c)
			s++;
		previous = s;
		while (*s != c && *s)
			s++;
		if (*s == c || s > previous)
		{
			*temparray = ft_substr(previous, 0, s - previous);
			temparray++;
		}
	}
	*temparray = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		size;

	if (!s)
		return (NULL);
	size = stringcount(s, c);
	array = (char **)malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	allocate(array, s, c);
	return (array);
}
