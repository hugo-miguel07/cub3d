/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collisions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 17:47:03 by htavares          #+#    #+#             */
/*   Updated: 2026/06/16 11:37:16 by htavares         ###   ########.fr       */
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

int	check_x_padding(t_game *game, t_mmplayerpos ppos, double nx, double p)
{
	int	ix;

	ix = (int)(nx + p);
	if (ix != ppos.px)
	{
		if (is_wall(game, ix, ppos.py))
			return (0);
	}
	ix = (int)(nx - p);
	if (ix != ppos.px)
	{
		if (is_wall(game, ix, ppos.py))
			return (0);
	}
	return (1);
}

int	check_y_padding(t_game *game, t_mmplayerpos ppos, double ny, double p)
{
	int	iy;

	iy = (int)(ny + p);
	if (iy != ppos.py)
	{
		if (is_wall(game, ppos.px, iy))
			return (0);
	}
	iy = (int)(ny - p);
	if (iy != ppos.py)
	{
		if (is_wall(game, ppos.px, iy))
			return (0);
	}
	return (1);
}
