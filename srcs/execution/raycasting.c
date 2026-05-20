/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:32:42 by htavares          #+#    #+#             */
/*   Updated: 2026/05/20 14:34:09 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_game *game, t_rt_state *rt, int x)
{
	rt->cameraX = 2.0 * x / (double)game->frame->width - 1.0;
	rt->rayDirX = game->player.dirX + game->player.planeX * rt->cameraX;
	rt->rayDirY = game->player.dirY + game->player.planeY * rt->cameraX;
}

static void	run_dda_loop(t_game *game, t_rt_state *rt)
{
	rt->hit = 0;
	rt->side = 0;
	while (!rt->hit)
	{
		if (rt->sideDistX < rt->sideDistY)
		{
			rt->sideDistX += rt->deltaDistX;
			rt->mapX += rt->stepX;
			rt->side = 0;
		}
		else
		{
			rt->sideDistY += rt->deltaDistY;
			rt->mapY += rt->stepY;
			rt->side = 1;
		}
		if (is_outside_map(game, rt))
		{
			rt->hit = 1;
			break ;
		}
		if (game->file->map[rt->mapY][rt->mapX] == '1')
			rt->hit = 1;
	}
}

static void	compute_perp_dist(t_rt_state *rt)
{
	if (rt->side == 0)
		rt->perpWallDist = rt->sideDistX - rt->deltaDistX;
	else
		rt->perpWallDist = rt->sideDistY - rt->deltaDistY;
	if (rt->perpWallDist <= 0.0)
		rt->perpWallDist = 1e30;
}

void	cast_dda(t_game *game, t_rt_state *rt)
{
	double	px;
	double	py;

	init_dda_params(game, rt, &px, &py);
	init_steps(rt, px, py);
	run_dda_loop(game, rt);
	compute_perp_dist(rt);
}

void	calc_wall_height(t_game *game, t_rt_state *rt)
{
	rt->lineHeight = (int)(game->frame->height / rt->perpWallDist);
	rt->drawStart = -rt->lineHeight / 2 + game->frame->height / 2;
	if (rt->drawStart < 0)
		rt->drawStart = 0;
	rt->drawEnd = rt->lineHeight / 2 + game->frame->height / 2;
	if (rt->drawEnd >= game->frame->height)
		rt->drawEnd = game->frame->height - 1;
	rt->color = 0x00FFFFFF;
	if (rt->side == 1)
		rt->color = (rt->color >> 1) & 8355711;
}
