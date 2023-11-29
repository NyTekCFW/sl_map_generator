/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 03:27:33 by lchiva            #+#    #+#             */
/*   Updated: 2023/11/25 09:05:11 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sl_map_gen.h"

static int	sl_spread_for_item(char **arr, int row, int column)
{
	int	i;

	i = 0;
	i += sl_find_item(arr, row - 1, column);
	i += sl_find_item(arr, row + 1, column);
	i += sl_find_item(arr, row, column - 1);
	i += sl_find_item(arr, row, column + 1);
	return (i);
}

int	sl_find_item(char **arr, int row, int column)
{
	int	i;

	i = 0;
	if (arr[row][column] == ITEM)
	{
		arr[row][column] = CHITEM;
		i += 1;
		i += sl_spread_for_item(arr, row, column);
		return (i);
	}
	else if (arr[row][column] == EMPTY || arr[row][column] == EXIT
	|| arr[row][column] == PLAYER || arr[row][column] == MOB)
	{
		if (arr[row][column] == EMPTY)
			arr[row][column] = CHECKED;
		if (arr[row][column] == EXIT)
			arr[row][column] = CHEXIT;
		if (arr[row][column] == MOB)
			arr[row][column] = CHMOB;
		i += sl_spread_for_item(arr, row, column);
		return (i);
	}
	else
		return (0);
}

static int	sl_find_exit(char **arr, int row, int column)
{
	int	i;

	i = 0;
	if (arr[row][column] == EXIT)
	{
		arr[row][column] = CHEXIT;
		return (1);
	}
	else if (arr[row][column] == EMPTY || arr[row][column] == ITEM
	|| arr[row][column] == PLAYER || arr[row][column] == MOB)
	{
		if (arr[row][column] == EMPTY)
			arr[row][column] = CHECKED;
		if (arr[row][column] == ITEM)
			arr[row][column] = CHITEM;
		if (arr[row][column] == MOB)
			arr[row][column] = CHMOB;
		i += sl_find_exit(arr, row - 1, column);
		i += sl_find_exit(arr, row + 1, column);
		i += sl_find_exit(arr, row, column - 1);
		i += sl_find_exit(arr, row, column + 1);
		return (i);
	}
	else
		return (0);
}

int	sl_find_path(char **arr, int nb)
{
	int	player_row;
	int	player_column;

	player_row = 0;
	player_column = 0;
	sl_find_player_pos(arr, &player_column, &player_row);
	if (sl_find_exit(arr, player_row, player_column))
	{
		sl_reset_map(arr);
		if (sl_find_item(arr, player_row, player_column) == nb)
		{
			sl_reset_map(arr);
			return (1);
		}
	}
	return (0);
}
