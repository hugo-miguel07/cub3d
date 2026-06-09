/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:30:23 by htavares          #+#    #+#             */
/*   Updated: 2026/05/22 12:27:11 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clean_buffer(t_game *game)
{
	int	size;

	size = game->frame->line_length * game->frame->height;
	ft_bzero(game->frame->pixels, size);
}

static void	draw_floor_ceiling(t_game *game)
{
	int				x;
	int				y;
	unsigned int	ceil_c;
	unsigned int	floor_c;

	ceil_c = parse_rgb(game->file->c_color[1]);
	floor_c = parse_rgb(game->file->f_color[1]);
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

void	draw_scene(t_game *game)
{
	if (!game || !game->mlx || !game->win || !game->frame || !game->zbuffer)
		return ;
	clean_buffer(game);
	draw_floor_ceiling(game);
	draw_map(game);
	draw_minimap(game);
}
