/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_map_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 03:45:06 by lchiva            #+#    #+#             */
/*   Updated: 2023/11/29 19:59:56 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sl_map_gen.h"

int	sl_dimension_check(char **argv)
{
	int	width;
	int	height;

	width = sl_atoi(argv[2]);
	height = sl_atoi(argv[3]);
	if (((width * height) + height + 1) <= 44100)
	{
		if ((width > 4 && height > 2) || (width > 2 && height > 4))
		{
			if(width != height)
				return (1);
			else
				write(1, "\033[31mError : Map need to be a rectangle\n", 40);
		}
		else
			write(1, "\033[31mError : Map need to be >= than 3x5 or 5x3\n", 47);
	}
	else
		write(1, "\033[31mError : Map allocation bigger than 44 100 (210x210)\n", 57);
	return (0);
}

int	sl_check_arg(int argc, char **argv)
{
	int	a;
	int	b;

	a = 2;
	b = 0;
	while (a < argc)
	{
		b = 0;
		while (argv[a][b])
		{
			if (argv[a][b] < '0' && argv[a][b] > '9')
				return (0);
			b++;
		}
		a++;
	}
	return (1);
}

int	sl_is_valid(int argc, char **argv)
{
	if (argc >= 4 && argc <= 6)
	{
		if (sl_check_arg(argc, argv))
		{
			if (sl_dimension_check(argv))
				return (1);
		}
		else
			write(1, "\033[31mError: Only numbers are supported\n", 39);
	}
	else
		write(1, "\033[31mError: Invalid number of arguments\n", 40);
	return (0);
}

int	sl_init_map(t_gmap *mapping, int argc, char **argv)
{
	mapping->input = 0;
	mapping->x = 0;
	mapping->y = 0;
	mapping->width = sl_atoi(argv[2]);
	mapping->height = sl_atoi(argv[3]);
	mapping->size = mapping->width * mapping->height + mapping->height;
	if (argc >= 5)
		mapping->max_collector = sl_atoi(argv[4]);
	if (argc >= 6)
		mapping->max_wall = sl_atoi(argv[5]);
	mapping->m_map = (char *)sl_calloc(mapping->size + 1, sizeof(char));
	if (!mapping->m_map)
		return (sl_bzero(mapping, sizeof(t_gmap)), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_gmap mapping;

	sl_bzero(&mapping, sizeof(t_gmap));
	srand((unsigned int)time(NULL));
	print_credits();
	if (sl_is_valid(argc, argv))
	{
		if (sl_init_map(&mapping, argc, argv))
		{
			sl_init_base_map(&mapping);
			sl_export_map(argv[1], mapping.m_map);
		}
		else
			write(1, "\033[31mError : Malloc Failed\n", 27);
	}
	if (mapping.m_map)
		free(mapping.m_map);
	sl_bzero(&mapping, sizeof(t_gmap));
	write(1, "Closing map generator...\n", 26);
	return (0);
}
//cc sl_atoi.c sl_check.c sl_final_check.c sl_func.c sl_map_gen.c sl_map_init.c sl_utils.c
