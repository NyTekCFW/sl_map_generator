/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_file_exporter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:35:18 by lchiva            #+#    #+#             */
/*   Updated: 2023/11/29 19:25:13 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sl_map_gen.h"

static char *sl_mapname(char *name)
{
	char	*ext;
	char	*mc;
	int		size;
	int		index;

	ext = ".ber";
	index = 0;
	size = sl_strlen(name);
	mc = sl_calloc(size + 5, sizeof(char));
	if (!mc)
		return (0);
	while (index < size + 4)
	{
		if (index < size)
			mc[index] = name[index];
		else
			mc[index] = ext[index - size];
		index++;
	}
	return (mc);
}

static unsigned long	sl_hashstr(const char *str)
{
	unsigned long	hash;

	hash = 2784;
	while (*str++)
		hash = ((hash << 5) + hash) + (int)*str;
	return (hash);
}

static char	*sl_getfiletype(char *filename)
{
	size_t	len;

	len = sl_strlen(filename) -1;
	while (filename[len])
	{
		if (filename[len] == '.' && filename[len + 1])
			return ((char *)&filename[len]);
		len--;
	}
	return ("none");
}

void	sl_export_map(char *name, char *map)
{
	int	is_mc;
	int	fd;

	is_mc = 0;
	if (sl_hashstr(sl_getfiletype(name)) != sl_hashstr(".ber"))
	{
		name = sl_mapname(name);
		is_mc = 1;
	}
	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd > 0)
	{
		write(fd, map, sl_strlen(map));
		close(fd);
		write(1, "\033[32mMap exported.\033[0m\n", 24);
	}
	else
		write(1, "\033[31mError: during exportion of map\n", 36);
	if (is_mc && name)
		free(name);
}
