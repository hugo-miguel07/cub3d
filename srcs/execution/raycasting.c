/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:32:42 by htavares          #+#    #+#             */
/*   Updated: 2026/05/22 12:39:11 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_game *game, t_rt_state *rt, int x)
{
	rt->camerax = 2.0 * x / (double)game->frame->width - 1.0;
	rt->raydirx = game->player.dirx + game->player.planex * rt->camerax;
	rt->raydiry = game->player.diry + game->player.planey * rt->camerax;
}

static void	run_dda_loop(t_game *game, t_rt_state *rt)
{
	rt->hit = 0;
	rt->side = 0;
	while (!rt->hit)
	{
		if (rt->sidedistx < rt->sidedisty)
		{
			rt->sidedistx += rt->deltadistx;
			rt->mapx += rt->stepx;
			rt->side = 0;
		}
		else
		{
			rt->sidedisty += rt->deltadisty;
			rt->mapy += rt->stepy;
			rt->side = 1;
		}
		if (is_outside_map(game, rt))
		{
			rt->hit = 1;
			break ;
		}
		if (game->file->map[rt->mapy][rt->mapx] == '1')
			rt->hit = 1;
	}
}

static void	compute_perp_dist(t_rt_state *rt)
{
	if (rt->side == 0)
		rt->perpwalldist = rt->sidedistx - rt->deltadistx;
	else
		rt->perpwalldist = rt->sidedisty - rt->deltadisty;
	if (rt->perpwalldist <= 0.0)
		rt->perpwalldist = 1e30;
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
	rt->lineheight = (int)(game->frame->height / rt->perpwalldist);
	rt->drawstart = -rt->lineheight / 2 + game->frame->height / 2;
	if (rt->drawstart < 0)
		rt->drawstart = 0;
	rt->drawend = rt->lineheight / 2 + game->frame->height / 2;
	if (rt->drawend >= game->frame->height)
		rt->drawend = game->frame->height - 1;
	rt->color = 0x00FFFFFF;
	if (rt->side == 1)
		rt->color = (rt->color >> 1) & 8355711;
}
