/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:05:22 by marvin            #+#    #+#             */
/*   Updated: 2022/10/27 10:05:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)dest;
	p2 = (unsigned char *)src;
	if (!p1 && !p2)
		return (p1);
	i = 0;
	while (i < n)
	{
		p1[i] = p2[i];
		i++;
	}
	return (p1);
}
