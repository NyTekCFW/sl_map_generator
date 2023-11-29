/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 06:17:25 by lchiva            #+#    #+#             */
/*   Updated: 2023/11/25 07:16:21 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sl_map_gen.h"

static int	sl_isspace(int c)
{
	if ((c >= 0x09 && c <= 0x0D) || (c == 0x20))
		return (1);
	return (0);
}

int	sl_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	mp;

	mp = 1;
	res = 0;
	i = 0;
	while (nptr[i] && sl_isspace(nptr[i]) == 1)
		i++;
	if ((nptr[i] && nptr[i] == '+') || (nptr[i] && nptr[i] == '-'))
	{
		if (nptr[i] == '-')
			mp *= -1;
		i++;
	}
	while (nptr[i] && nptr[i] >= 0x30 && nptr[i] <= 0x39)
		res = (res * 10) + (nptr[i++] - 0x30);
	return (res * mp);
}

int	sl_strlen(char *ln)
{
	int	i;

	i = 0;
	while (ln[i])
		i++;
	return (i);
}

int	ft_finder(char *map)
{
	int a;

	a = 0;
	while (map[a])
	{
		if (map[a] == '\n')
			return (a + 1);
		a++;
	}
	return (a);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dest;
	s = src;
	if (!dest && !src)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dest);
}