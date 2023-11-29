/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 03:46:21 by lchiva            #+#    #+#             */
/*   Updated: 2023/11/29 20:12:21 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sl_map_gen.h"

int randomInRange(int min, int max)
{
	int	rnd;

	rnd = rand() % (max - min + 1) + min;
	return (rnd);
}

void sl_clearscreen()
{
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

void	sl_bzero(void *s, size_t n)
{
	char	*c;

	c = s;
	while (n--)
		*c++ = 0;
}

void	*sl_calloc(size_t nmemb, size_t size)
{
	void	*mc;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (((size * nmemb) / nmemb) != size)
		return (NULL);
	mc = malloc(nmemb * size);
	if (!mc)
		return (NULL);
	sl_bzero(mc, nmemb * size);
	return (mc);
}

void	print_credits()
{
	sl_clearscreen();
	write(1, "\033[1m.-----------------.\n", 24);
	write(1, "| .--------------. |\n", 21);
	write(1, "| | ____  _____  | |\n", 21);
	write(1, "| ||_   \\|_   _| | |\n", 21);
	write(1, "| |  |   \\ | |   | |\n", 21);
	write(1, "| |  | |\\ \\| |   | |\n", 21);
	write(1, "| | _| |_\\   |_  | |\n", 21);
	write(1, "| ||_____|\\____| | |\n", 21);
	write(1, "| |              | |\n", 21);
	write(1, "| '--------------' |\n", 21);
	write(1, " '----------------' \n", 21);
	write(1, "\nSo_Long map generator (v1.0.0 Beta)\n\n", 38);
	write(1, "Credits :\n\033[5m\033[32mNyTek\033[36mCFW \033[37m\033[0m\033[1m@lchiva (creator)\n@nrossa		 (helper)\033[0m\n\n", 88);
}
