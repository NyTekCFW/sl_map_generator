/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_map_gen.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 03:27:41 by lchiva            #+#    #+#             */
/*   Updated: 2023/11/29 18:57:14 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stddef.h>
# include <stdarg.h>
# include <limits.h>
# include <fcntl.h>
# include <malloc.h>
# include <time.h>

typedef struct gmap_s
{
	int		x;
	int		y;
	int		c_wall;
	int		c_ground;
	int		c_collector;
	int		width;
	int		height;
	int		size;
	char	*m_map;
	char	**c_map;
	int		input;
	int		max_collector;
	int		max_wall;
	int		fail;
}	t_gmap;

enum	e_map
{
	EMPTY = 48,
	WALL,
	TEMPTY,
	ITEM = 67,
	EXIT = 69,
	MOB = 77,
	PLAYER = 80,
	PEXIT,
	PATK,
	PATKEX,
	CHECKED = 54,
	CHEXIT,
	CHITEM,
	CHMOB
};
int		sl_strlen(char *ln);
int		sl_fail(t_gmap *mapping);
int		sl_find_path(char **arr, int nb);
int		randomInRange(int min, int max);
int		sl_atoi(const char *nptr);
int		sl_str_to_array(t_gmap *mapping);
int		sl_find_item(char **arr, int row, int column);
int		ft_finder(char *map);
void	sl_init_base_map(t_gmap *mapping);
void	sl_clearscreen();
void	sl_bzero(void *s, size_t n);
void	*sl_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	print_credits();
void	sl_attempt(t_gmap *mapping, int *attempt);
void	sl_reset_map(char **arr);
void	sl_find_player_pos(char **arr, int *x, int *y);
void	sl_export_map(char *name, char *map);
#endif