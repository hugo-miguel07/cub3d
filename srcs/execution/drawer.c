/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:30:23 by htavares          #+#    #+#             */
/*   Updated: 2026/05/19 17:22:02 by htavares         ###   ########.fr       */
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

static unsigned int	get_texel(t_texture *tex, int x, int y)
{
	char	*dst;
	int		offset;

	if (!tex || !tex->pixels)
		return (0);
	if (x < 0 || y < 0 || x >= tex->width || y >= tex->height)
		return (0);
	offset = (y * tex->line_length) + (x * (tex->bits_per_pix / 8));
	dst = (char *)tex->pixels + offset;
	return (*(unsigned int *)dst);
}

static void	draw_map(t_game *game)
{
	int			x;
	int			y;
	t_rt_state	rt;
	double		wall_x;
	int			ex_x;
	int			ex_y;
	double		step;
	double		tex_pos;
	unsigned int	color;

	if (!game || !game->file || !game->frame || !game->zbuffer)
		return ;
	x = 0;
	while (x < game->frame->width)
	{
		ft_bzero(&rt, sizeof(rt));
		init_ray(game, &rt, x);
		cast_dda(game, &rt);
		calc_wall_height(game, &rt);
		rt.tex = NULL;
		if (rt.side == 0)
		{
			if (rt.rayDirX < 0)
				rt.tex = &game->textures.we;
			else
				rt.tex = &game->textures.ea;
		}
		else
		{
			if (rt.rayDirY < 0)
				rt.tex = &game->textures.no;
			else
				rt.tex = &game->textures.so;
		}
		if (rt.drawStart > rt.drawEnd)
		{
			game->zbuffer[x] = rt.perpWallDist;
			x++;
			continue;
		}
		game->zbuffer[x] = rt.perpWallDist;
		if (rt.side == 0)
			wall_x = game->player.py + rt.perpWallDist * rt.rayDirY;
		else
			wall_x = game->player.px + rt.perpWallDist * rt.rayDirX;
		wall_x -= floor(wall_x);
		ex_x = (int)(wall_x * (double)rt.tex->width);
		if (rt.side == 0 && rt.rayDirX > 0)
			ex_x = rt.tex->width - ex_x - 1;
		if (rt.side == 1 && rt.rayDirY < 0)
			ex_x = rt.tex->width - ex_x - 1;
		step = 1.0 * rt.tex->height / rt.lineHeight;
		tex_pos = (rt.drawStart - game->frame->height / 2
				+ rt.lineHeight / 2) * step;
		y = rt.drawStart - 1;
		while (++y <= rt.drawEnd)
		{
			ex_y = (int)tex_pos;
			if (ex_y < 0)
				ex_y = 0;
			else if (ex_y >= rt.tex->height)
				ex_y = rt.tex->height - 1;
			tex_pos += step;
			color = get_texel(rt.tex, ex_x, ex_y);
			if (rt.side == 1)
				color = (color >> 1) & 8355711;
			put_pixel(game->frame, x, y, color);
		}
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
