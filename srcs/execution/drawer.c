/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:30:23 by htavares          #+#    #+#             */
/*   Updated: 2026/05/13 14:11:54 by htavares         ###   ########.fr       */
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
	int x;
	int mapX;
	int mapY;
	int stepX;
	int stepY;
	int hit;
	int side;
	double cameraX;
	double rayDirX;
	double rayDirY;
	double deltaDistX;
	double deltaDistY;
	double sideDistX;
	double sideDistY;
	double perpWallDist;
	int drawStart;
	int drawEnd;
	int lineHeight;
	unsigned int color;

	if (!game || !game->file || !game->frame || !game->zbuffer)
		return ;

	x = 0;
	while (x < game->frame->width)
	{
		/* camera x: -1 (left) -> 1 (right) */
		cameraX = 2.0 * x / (double)game->frame->width - 1.0;
		rayDirX = game->player.dirX + game->player.planeX * cameraX;
		rayDirY = game->player.dirY + game->player.planeY * cameraX;

		mapX = (int)game->player.px;
		mapY = (int)game->player.py;

		deltaDistX = (rayDirX == 0.0) ? 1e30 : fabs(1.0 / rayDirX);
		deltaDistY = (rayDirY == 0.0) ? 1e30 : fabs(1.0 / rayDirY);

		/* calculate step and initial sideDist */
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player.px - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player.px) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player.py - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player.py) * deltaDistY;
		}

		/* DDA */
		hit = 0;
		side = 0;
		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			/* bounds check and hit test (map uses '1' for walls) */
			if (!game->file->map[mapX] || mapY < 0 || !game->file->map[mapX][mapY])
			{
				/* out of map - treat as hit */
				hit = 1;
				break ;
			}
			if (game->file->map[mapX][mapY] == '1')
				hit = 1;
		}

		if (side == 0)
			perpWallDist = sideDistX - deltaDistX;
		else
			perpWallDist = sideDistY - deltaDistY;

		if (perpWallDist <= 0.0)
			perpWallDist = 1e30;

		game->zbuffer[x] = perpWallDist;

		/* optional simple vertical stripe to visualize walls (skeleton)
		   choose white and shade y-sides darker */
		lineHeight = (int)(game->frame->height / perpWallDist);
		drawStart = -lineHeight / 2 + game->frame->height / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + game->frame->height / 2;
		if (drawEnd >= game->frame->height)
			drawEnd = game->frame->height - 1;
		color = 0x00FFFFFF;
		if (side == 1)
			color = (color >> 1) & 8355711;
		for (int y = drawStart; y <= drawEnd; ++y)
			put_pixel(game->frame, x, y, color);

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
