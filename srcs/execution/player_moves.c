/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 17:16:57 by htavares          #+#    #+#             */
/*   Updated: 2026/06/16 11:35:54 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	canmove(t_game *game, double nx, double ny)
{
	t_mmplayerpos	ppos;
	double			p;

	if (!game || !game->file || !game->file->map)
		return (0);
	ppos.px = (int)nx;
	ppos.py = (int)ny;
	if (is_wall(game, ppos.px, ppos.py))
		return (0);
	p = PLAYERCOLLISION;
	if (!check_x_padding(game, ppos, nx, p))
		return (0);
	if (!check_y_padding(game, ppos, ny, p))
		return (0);
	return (1);
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
	game->player.dirx = cos(game->player.angle);
	game->player.diry = sin(game->player.angle);
	plane_len = tan(FOV / 2.0);
	game->player.planex = -game->player.diry * plane_len;
	game->player.planey = game->player.dirx * plane_len;
	return (0);
}

static int	move_frontback(t_game *g, double *nx, double *ny, double ss)
{
	int	moved;

	moved = 0;
	if (g->input.w)
	{
		*ny += g->player.diry * ss;
		*nx += g->player.dirx * ss;
		moved = 1;
	}
	else if (g->input.s)
	{
		*ny -= g->player.diry * ss;
		*nx -= g->player.dirx * ss;
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
		*ny += g->player.dirx * ss;
		*nx += -g->player.diry * ss;
		moved = 1;
	}
	else if (g->input.d)
	{
		*ny -= g->player.dirx * ss;
		*nx -= -g->player.diry * ss;
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
