/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:30:23 by htavares          #+#    #+#             */
/*   Updated: 2026/05/15 15:01:20 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clean_buffer(t_game *game)
{
	int	size;

	size = game->frame->line_length * game->frame->height;
	ft_bzero(game->frame->pixels, size);
}


static void draw_floor_ceiling(t_game *game)
{
	int				x;
	int				y;
	unsigned int	ceil_c;
	unsigned int	floor_c;

	ceil_c = parse_rgb(game->file->C_color[1]);
	floor_c = parse_rgb(game->file->F_color[1]);
	y = 0;
	while (y < game->frame->height)
    {
		x = 0;
		while (x < game->frame->width)
		{
			if (y < game->frame->height / 2)
				put_pixel(game->frame, x, y, ceil_c);
			else
				put_pixel(game->frame, x, y, floor_c);
			x++;
		}
		y++;
	}
}
/*Esta funcao esta completamente COPILOT, tenho que refazer e entender*/
static void	draw_map(t_game *game)
{
	int			x;
	int			y;
	t_rt_state	rt;

	if (!game || !game->file || !game->frame || !game->zbuffer)
		return ;
	x = 0;
	while (x < game->frame->width)
	{
		ft_bzero(&rt, sizeof(rt));
		init_ray(game, &rt, x);
		cast_dda(game, &rt);
		calc_wall_height(game, &rt);
		if (rt.drawStart > rt.drawEnd)
		{
			game->zbuffer[x] = rt.perpWallDist;
			x++;
			continue;
		}
		game->zbuffer[x] = rt.perpWallDist;
		y = rt.drawStart - 1;
		while (++y <= rt.drawEnd)
			put_pixel(game->frame, x, y, rt.color);
		x++;
	}
}

void	draw_scene(t_game *game)
{
	if (!game || !game->mlx || !game->win || !game->frame || !game->zbuffer)
		return ;
	clean_buffer(game);
	draw_floor_ceiling(game);
	draw_map(game);
}
