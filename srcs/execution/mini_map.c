/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 10:28:18 by htavares          #+#    #+#             */
/*   Updated: 2026/06/16 11:27:14 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_to_default(t_minimap *mm)
{
	mm->height = 0;
	mm->width = 0;
	mm->radius = 5;
	mm->x_offset = 5;
	mm->y_offset = 5;
	mm->tile_size = 8;
	mm->color = 0;
}

static void	coloring_minimap(t_frame *frame, int start_x, int start_y,
		t_minimap *mm)
{
	int	x;
	int	y;

	if (!frame || mm->tile_size <= 0)
		return ;
	if (mm->color == 0x00000000)
		return ;
	y = 0;
	while (y < mm->tile_size)
	{
		x = 0;
		while (x < mm->tile_size)
		{
			put_pixel(frame, start_x + x, start_y + y, mm->color);
			x++;
		}
		y++;
	}
}

static void	draw_map2d(t_game *game, t_minimap *mm)
{
	int	mapy;
	int	mapx;
	int	maph;

	mapy = -1;
	maph = get_map_height(game->file->map);
	while (game->file->map[++mapy])
	{
		mapx = -1;
		while (game->file->map[mapy][++mapx])
		{
			if (game->file->map[mapy][mapx] == '1')
				mm->color = 0x00FFFFFF;
			else if (game->file->map[mapy][mapx] == '0'
				|| game->file->map[mapy][mapx] == 'N'
				|| game->file->map[mapy][mapx] == 'S'
				|| game->file->map[mapy][mapx] == 'E'
				|| game->file->map[mapy][mapx] == 'W')
				mm->color = 0x00333333;
			else
				mm->color = 0x00000000;
			coloring_minimap(game->frame, (mapx + mm->x_offset) * mm->tile_size,
				((maph - 1 - mapy) + mm->y_offset) * mm->tile_size, mm);
		}
	}
}

static void	draw_player(t_game *game, t_minimap *mm)
{
	t_mmplayerpos	ppos;
	int				x;
	int				y;
	int				size;
	int				map_h;

	size = 8;
	ppos.px = (int)((mm->x_offset + game->player.px)
			* mm->tile_size) - (size / 2);
	map_h = get_map_height(game->file->map);
	ppos.py = (int)(((mm->y_offset + (map_h - game->player.py))
				* mm->tile_size)) - (size / 2);
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			put_pixel(game->frame, ppos.px + x, ppos.py + y, 0x00FF0000);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game *game)
{
	t_minimap	mini_map;

	if (!game || !game->frame || !game->file || !game->file->map)
		return ;
	set_to_default(&mini_map);
	draw_map2d(game, &mini_map);
	draw_player(game, &mini_map);
}
