/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collisions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:47:03 by htavares          #+#    #+#             */
/*   Updated: 2026/06/08 18:15:50 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_game *game, int x, int y)
{
	if (y < 0 || !game->file->map[y])
		return (1);
	if (x < 0 || !game->file->map[y][x])
		return (1);
	return (game->file->map[y][x] == '1');
}

int	check_x_padding(t_game *game, int mx, int my, double nx, double p)
{
	int	ix;

	ix = (int)(nx + p);
	if (ix != mx)
	{
		if (is_wall(game, ix, my))
			return (0);
	}
	ix = (int)(nx - p);
	if (ix != mx)
	{
		if (is_wall(game, ix, my))
			return (0);
	}
	return (1);
}

int	check_y_padding(t_game *game, int mx, int my, double ny, double p)
{
	int	iy;

	iy = (int)(ny + p);
	if (iy != my)
	{
		if (is_wall(game, mx, iy))
			return (0);
	}
	iy = (int)(ny - p);
	if (iy != my)
	{
		if (is_wall(game, mx, iy))
			return (0);
	}
	return (1);
}
