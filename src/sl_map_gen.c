/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_map_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 03:45:21 by lchiva            #+#    #+#             */
/*   Updated: 2023/11/29 19:38:42 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sl_map_gen.h"

void sl_insert_multiple(t_gmap *mapping, char c, int max)
{
	int	attempt;

	attempt = 0;
	mapping->x = mapping->width + 2;
	mapping->input = (randomInRange(0, mapping->width - 2) * randomInRange(1, mapping->height - 2));
	if (max <= 0 || max >= mapping->c_ground)
		max = randomInRange(1, (mapping->c_ground / 10) + 1);
	while (max > 0)
	{
		attempt = 0;
		while (mapping->m_map[mapping->x + mapping->input] != 0x30)
		{
			mapping->input = (randomInRange(0, mapping->width - 2) * randomInRange(1, mapping->height - 2));
			sl_attempt(mapping, &attempt);
		}
		mapping->m_map[mapping->x + mapping->input] = c;
		mapping->c_ground--;
		max--;
	}
}

void sl_insert_ground(t_gmap *mapping)
{
	mapping->input = 0;
	mapping->x = mapping->width + 2;
	while ((mapping->x + mapping->input) < (mapping->size - mapping->width))
	{
		mapping->m_map[mapping->x + mapping->input] = 0x30;
		if (mapping->input == mapping->width - 2)
		{
			mapping->m_map[mapping->x + mapping->input] = 0x31;
			mapping->x += mapping->width + 1;
			mapping->input = 0;
		}
		else
			mapping->input++;
	}
}

void sl_map_gen(t_gmap *mapping)
{
	while ((mapping->x + mapping->input) < mapping->size)
	{
		mapping->m_map[mapping->x + mapping->input] = 0x31;
		if (mapping->input == mapping->width)
		{
			mapping->m_map[mapping->x + mapping->input] = '\n';
			mapping->x += mapping->input + 1;
			mapping->input = 0;
		}
		else
			mapping->input++;
	}
	mapping->m_map[mapping->x - 1] = 0;
}

void	sl_count_brush(t_gmap *mapping)
{
	int	index;

	index = 0;
	mapping->c_wall = 0;
	mapping->c_ground = 0;
	mapping->c_collector = 0;
	while (mapping->m_map[index])
	{
		if (mapping->m_map[index] == 0x31)
			mapping->c_wall++;
		if (mapping->m_map[index] == 0x30)
			mapping->c_ground++;
		if (mapping->m_map[index] == 'C')
			mapping->c_collector++;
		index++;
	}
}

void	sl_init_base_map(t_gmap *mapping)
{
	int	v;

	v = 0;
	while (!v)
	{
		sl_map_gen(mapping);
		sl_insert_ground(mapping);
		sl_count_brush(mapping);
		sl_insert_multiple(mapping, 'P', 1);
		sl_insert_multiple(mapping, 'E', 1);
		sl_insert_multiple(mapping, 'C', mapping->max_collector);
		sl_insert_multiple(mapping, '1', mapping->max_wall);
		sl_count_brush(mapping);
		if (sl_str_to_array(mapping))
			v = 1;
		else
		{
			if (sl_fail(mapping))
				return ;
		}
	}
	write(1, mapping->m_map, sl_strlen(mapping->m_map));
	write(1, "\n----------------\n", 19);
	printf("Map generated with %i fail(s)\n", mapping->fail);
}
