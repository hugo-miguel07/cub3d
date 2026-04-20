/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:11:06 by htavares          #+#    #+#             */
/*   Updated: 2026/04/20 17:21:42 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
				p.x = x;
				p.y = y;
				p.orientation = map[y][x];
				return (p);
			}
			x++;
		}
		y++;
	}
	p.x = -1;
	p.y = -1;
	return (p);
}
