/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:29:23 by htavares          #+#    #+#             */
/*   Updated: 2026/05/20 14:32:33 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_dda_params(t_game *game, t_rt_state *rt, double *px, double *py)
{
	*px = game->player.px;
	*py = game->player.py;
	rt->mapX = (int)(*px);
	rt->mapY = (int)(*py);
	if (rt->rayDirX == 0.0)
		rt->deltaDistX = 1e30;
	else
		rt->deltaDistX = fabs(1.0 / rt->rayDirX);
	if (rt->rayDirY == 0.0)
		rt->deltaDistY = 1e30;
	else
		rt->deltaDistY = fabs(1.0 / rt->rayDirY);
}

void	init_steps(t_rt_state *rt, double px, double py)
{
	if (rt->rayDirX < 0)
	{
		rt->stepX = -1;
		rt->sideDistX = (px - rt->mapX) * rt->deltaDistX;
	}
	else
	{
		rt->stepX = 1;
		rt->sideDistX = (rt->mapX + 1.0 - px) * rt->deltaDistX;
	}
	if (rt->rayDirY < 0)
	{
		rt->stepY = -1;
		rt->sideDistY = (py - rt->mapY) * rt->deltaDistY;
	}
	else
	{
		rt->stepY = 1;
		rt->sideDistY = (rt->mapY + 1.0 - py) * rt->deltaDistY;
	}
}

int	is_outside_map(t_game *game, t_rt_state *rt)
{
	if (rt->mapY < 0 || !game->file->map[rt->mapY])
		return (1);
	if (rt->mapX < 0 || !game->file->map[rt->mapY][rt->mapX])
		return (1);
	return (0);
}
