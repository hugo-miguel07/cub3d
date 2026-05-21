/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:22:56 by antabord          #+#    #+#             */
/*   Updated: 2026/05/21 18:17:20 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	flood_fill(s_file *file, char **map, int y, int x)
{
	if (y < 0 || !map[y] || x < 0 || x >= (int)ft_strlen(map[y]))
		return (free_arr(map, map_size(map)), exit_check(INVALID_WALLS, file), 0);
	if (map[y][x] == 'V' || map[y][x] == '1')
		return (0);
	if (map[y][x] == ' ' || map[y][x] == '\t')
		return (free_arr(map, map_size(map)), exit_check(INVALID_WALLS, file), 0);
	map[y][x] = 'V';
	flood_fill(file, map, y + 1, x);
	flood_fill(file, map, y - 1, x);
	flood_fill(file, map, y, x + 1);
	flood_fill(file, map, y, x - 1);
	return (1);
}

int	player_pos(s_file *file, char **cpy)
{
	int	x;
	int	y;

	y = 0;
	while (cpy[y])
	{
		x = 0;
		while (cpy[y][x])
		{
			if (cpy[y][x] == 'N' || cpy[y][x] == 'S' || cpy[y][x] == 'W'
				|| cpy[y][x] == 'E')
				{
					if (!flood_fill(file, cpy, y, x))
						return (0);
				}
			x++;
		}
		y++;
	}
	return (1);
}
