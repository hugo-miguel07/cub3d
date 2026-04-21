/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:11:06 by htavares          #+#    #+#             */
/*   Updated: 2026/04/21 16:17:07 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	find_player(char **map)
{
	t_point	p;
	int		y;
	int		x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N'|| map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
			{
				p.x = (double)x + 0.5;
				p.y = (double)y + 0.5;
				p.orientation = map[y][x];
				return (p);
			}
			x++;
		}
		y++;
	}
	p.x = -1.0;
	p.y = -1.0;
	return (p);
}
