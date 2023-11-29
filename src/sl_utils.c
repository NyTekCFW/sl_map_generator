/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <lchiva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 03:27:27 by lchiva            #+#    #+#             */
/*   Updated: 2023/11/25 11:09:55 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sl_map_gen.h"

int	sl_fail(t_gmap *mapping)
{
	sl_bzero(mapping->m_map, mapping->size);
	mapping->input = 0;
	mapping->x = 0;
	mapping->y = 0;
	mapping->fail++;
	if (mapping->fail >= 30000)
	{
		write(1, "\033[31mError : 30000 try reached\n", 31);
		return (1);
	}
	return (0);
}

void	sl_attempt(t_gmap *mapping, int *attempt)
{
	*attempt += 1;
	if (*attempt >= 200)
	{
		*attempt = 0;
		while ((mapping->x + *attempt) < mapping->size)
		{
			if (mapping->m_map[mapping->x + *attempt] == 0x30)
			{
				mapping->input = *attempt;
				break ;
			}
			*attempt += 1;
		}
	}
}

void	sl_find_player_pos(char **arr, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == PLAYER || arr[i][j] == PEXIT
				|| arr[i][j] == PATK || arr[i][j] == PATKEX)
			{
				*y = i;
				*x = j;
			}
			j++;
		}
		i++;
	}
}

void	sl_reset_map(char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == CHECKED)
				arr[i][j] = EMPTY;
			if (arr[i][j] == CHEXIT)
				arr[i][j] = EXIT;
			if (arr[i][j] == CHITEM)
				arr[i][j] = ITEM;
			if (arr[i][j] == CHMOB)
				arr[i][j] = MOB;
			j++;
		}
		i++;
	}
}

