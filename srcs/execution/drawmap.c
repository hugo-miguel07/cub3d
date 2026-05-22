/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 14:35:14 by htavares          #+#    #+#             */
/*   Updated: 2026/05/22 12:34:46 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	select_texture(t_game *game, t_rt_state *rt)
{
	rt->tex = NULL;
	if (rt->side == 0)
	{
		if (rt->raydirx < 0)
			rt->tex = &game->textures.we;
		else
			rt->tex = &game->textures.ea;
	}
	else
	{
		if (rt->raydiry < 0)
			rt->tex = &game->textures.no;
		else
			rt->tex = &game->textures.so;
	}
}

static int	prep_ray(t_game *game, t_rt_state *rt, int x)
{
	ft_bzero(rt, sizeof(*rt));
	init_ray(game, rt, x);
	cast_dda(game, rt);
	calc_wall_height(game, rt);
	game->zbuffer[x] = rt->perpwalldist;
	if (rt->lineheight <= 0 || rt->drawstart > rt->drawend)
		return (0);
	select_texture(game, rt);
	return (rt->tex != NULL);
}

static int	calc_tex_x(t_game *game, t_rt_state *rt)
{
	double	wall_x;
	int		ex_x;

	if (rt->side == 0)
		wall_x = game->player.py + rt->perpwalldist * rt->raydiry;
	else
		wall_x = game->player.px + rt->perpwalldist * rt->raydirx;
	wall_x -= floor(wall_x);
	ex_x = (int)(wall_x * (double)rt->tex->width);
	if (rt->side == 0 && rt->raydirx > 0)
		ex_x = rt->tex->width - ex_x - 1;
	if (rt->side == 1 && rt->raydiry < 0)
		ex_x = rt->tex->width - ex_x - 1;
	return (ex_x);
}

static void	draw_column(t_game *game, t_rt_state *rt, int x)
{
	double	tex_pos;
	double	step;
	int		ex_x;
	int		y;

	ex_x = calc_tex_x(game, rt);
	step = 1.0 * rt->tex->height / rt->lineheight;
	tex_pos = (rt->drawstart - game->frame->height / 2
			+ rt->lineheight / 2) * step;
	y = rt->drawstart;
	while (y <= rt->drawend)
	{
		rt->mapy = (int)tex_pos;
		if (rt->mapy < 0)
			rt->mapy = 0;
		if (rt->mapy >= rt->tex->height)
			rt->mapy = rt->tex->height - 1;
		tex_pos += step;
		rt->color = get_texel(rt->tex, ex_x, rt->mapy);
		if (rt->side == 1)
			rt->color = (rt->color >> 1) & 8355711;
		put_pixel(game->frame, x, y, rt->color);
		y++;
	}
}

void	draw_map(t_game *game)
{
	int			x;
	t_rt_state	rt;

	if (!game || !game->file || !game->frame || !game->zbuffer)
		return ;
	x = 0;
	while (x < game->frame->width)
	{
		if (prep_ray(game, &rt, x))
			draw_column(game, &rt, x);
		x++;
	}
}
