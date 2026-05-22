/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:29:23 by htavares          #+#    #+#             */
/*   Updated: 2026/05/22 12:33:17 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_dda_params(t_game *game, t_rt_state *rt, double *px, double *py)
{
	*px = game->player.px;
	*py = game->player.py;
	rt->mapx = (int)(*px);
	rt->mapy = (int)(*py);
	if (rt->raydirx == 0.0)
		rt->deltadistx = 1e30;
	else
		rt->deltadistx = fabs(1.0 / rt->raydirx);
	if (rt->raydiry == 0.0)
		rt->deltadisty = 1e30;
	else
		rt->deltadisty = fabs(1.0 / rt->raydiry);
}

void	init_steps(t_rt_state *rt, double px, double py)
{
	if (rt->raydirx < 0)
	{
		rt->stepx = -1;
		rt->sidedistx = (px - rt->mapx) * rt->deltadistx;
	}
	else
	{
		rt->stepx = 1;
		rt->sidedistx = (rt->mapx + 1.0 - px) * rt->deltadistx;
	}
	if (rt->raydiry < 0)
	{
		rt->stepy = -1;
		rt->sidedisty = (py - rt->mapy) * rt->deltadisty;
	}
	else
	{
		rt->stepy = 1;
		rt->sidedisty = (rt->mapy + 1.0 - py) * rt->deltadisty;
	}
}

int	is_outside_map(t_game *game, t_rt_state *rt)
{
	if (rt->mapy < 0 || !game->file->map[rt->mapy])
		return (1);
	if (rt->mapx < 0 || !game->file->map[rt->mapy][rt->mapx])
		return (1);
	return (0);
}
