/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 17:16:57 by htavares          #+#    #+#             */
/*   Updated: 2026/05/18 17:53:54 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	can_move(t_game *game, double nx, double ny)
{
	int	mx;
	int	my;

	if (!game || !game->file || !game->file->map)
		return (0);
	mx = (int)nx;
	my = (int)ny;
	if (my < 0 || !game->file->map[my])
		return (0);
	if (mx < 0 || !game->file->map[my][mx])
		return (0);
	return (game->file->map[my][mx] != '1');
}

int	look_player(int keycode, t_game *game)
{
	double	rotationspeed;
	double	plane_len;

	rotationspeed = ROTATIONSPEED;
	if (keycode == 65361) /* Left Arrow */
		game->player.angle += rotationspeed;
	else if (keycode == 65363) /* Right Arrow */
		game->player.angle -= rotationspeed;
	game->player.dirX = cos(game->player.angle);
	game->player.dirY = sin(game->player.angle);
	plane_len = tan(FOV / 2.0);
	game->player.planeX = -game->player.dirY * plane_len;
	game->player.planeY = game->player.dirX * plane_len;
    return (0);
}

int	move_player(int keycode, t_game *game)
{
	double	stepspeed;
	double	nx;
	double	ny;

	stepspeed = STEPSPEED;
	nx = game->player.px;
	ny = game->player.py;
	if (keycode == 119) /* W / Up */
	{
        ny += game->player.dirY * stepspeed;
		nx += game->player.dirX * stepspeed;
	}
    else if (keycode == 115) /* S / Down */
	{
		ny -= game->player.dirY * stepspeed;
		nx -= game->player.dirX * stepspeed;
	}
    else if (keycode == 97) /* A / Left */
	{
		ny += game->player.dirX * stepspeed;
		nx += -game->player.dirY * stepspeed;
	}
    else if (keycode == 100) /* D / Right */
	{
		ny -= game->player.dirX * stepspeed;
		nx -= -game->player.dirY * stepspeed;
	}
    if ((nx != game->player.px || ny != game->player.py) && can_move(game, nx, ny))
    {
        game->player.px = nx;
        game->player.py = ny;
    }
	return (0);
}
