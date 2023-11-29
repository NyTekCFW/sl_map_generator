/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_final_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 06:17:17 by lchiva            #+#    #+#             */
/*   Updated: 2023/11/29 19:54:48 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sl_map_gen.h"

int	sl_get_gnl(char *map)
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

int	sl_gnl_gen(t_gmap *mapping, int *a)
{
	char	*map;

	map = mapping->m_map;
	while (*a < mapping->height)
	{
		mapping->c_map[*a] = sl_calloc(mapping->width + 1, sizeof(char *));
		if (!mapping->c_map[*a])
		{
			*a -= 1;
			while (*a >= 0)
			{
				free(mapping->c_map[*a]);
				*a -= 1;
			}
			return (0);
		}
		ft_memcpy(mapping->c_map[*a], map, ft_finder(map));
		map += ft_finder(map);
		*a += 1;
	}
	return (1);
}

int	sl_str_to_array(t_gmap *mapping)
{
	int		v;
	int		a;

	a = 0;
	mapping->c_map = (char **)sl_calloc(mapping->height + 1, sizeof(char **));
	if (!mapping->c_map)
		return (0);
	v = sl_gnl_gen(mapping, &a);
	if (v)
	{
		v = sl_find_path(mapping->c_map, mapping->c_collector);
		a--;
		while (a >= 0)
		{
			free(mapping->c_map[a]);
			a--;
		}
	}
	free(mapping->c_map);
	return (v);
}
