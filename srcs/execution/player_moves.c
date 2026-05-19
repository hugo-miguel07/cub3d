/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 17:16:57 by htavares          #+#    #+#             */
/*   Updated: 2026/05/19 14:58:01 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	canmove(t_game *game, double nx, double ny)
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

int	look_player(t_game *game)
{
	double	rotationspeed;
	double	plane_len;
	int		rotated;

	rotationspeed = ROTATIONSPEED;
	rotated = 0;
	if (game->input.left)
	{
		game->player.angle += rotationspeed;
		rotated = 1;
	}
	if (game->input.right)
	{
		game->player.angle -= rotationspeed;
		rotated = 1;
	}
	if (!rotated)
		return (0);
	game->player.dirX = cos(game->player.angle);
	game->player.dirY = sin(game->player.angle);
	plane_len = tan(FOV / 2.0);
	game->player.planeX = -game->player.dirY * plane_len;
	game->player.planeY = game->player.dirX * plane_len;
    return (0);
}

static int	move_frontback(t_game *g, double *nx, double *ny, double ss)
{
	int	moved;

	moved = 0;
	if (g->input.w)
	{
		*ny += g->player.dirY * ss;
		*nx += g->player.dirX * ss;
		moved = 1;
	}
	else if (g->input.s)
	{
		*ny -= g->player.dirY * ss;
		*nx -= g->player.dirX * ss;
		moved = 1;
	}
	return (moved);
}

static int	move_sideways(t_game *g, double *nx, double *ny, double ss)
{
	int	moved;

	moved = 0;
	if (g->input.a)
	{
		*ny += g->player.dirX * ss;
		*nx += -g->player.dirY * ss;
		moved = 1;
	}
	else if (g->input.d)
	{
		*ny -= g->player.dirX * ss;
		*nx -= -g->player.dirY * ss;
		moved = 1;
	}
	return (moved);
}

int	move_player(t_game *g)
{
	double	stepspeed;
	double	nx;
	double	ny;
	int		moved;

	stepspeed = STEPSPEED;
	nx = g->player.px;
	ny = g->player.py;
	moved = 0;
	if (g->input.w || g->input.s)
		moved = move_frontback(g, &nx, &ny, stepspeed);
	if (g->input.a || g->input.d)
		moved = move_sideways(g, &nx, &ny, stepspeed);
	if (!moved)
		return (0);
    if ((nx != g->player.px || ny != g->player.py) && canmove(g, nx, ny))
    {
        g->player.px = nx;
        g->player.py = ny;
    }
	return (0);
}
