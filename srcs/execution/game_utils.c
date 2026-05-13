/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 12:30:55 by htavares          #+#    #+#             */
/*   Updated: 2026/05/13 13:09:43 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_playerpos(t_game *game, int x, int y)
{
	game->player.px = (double) x + 0.5;
	game->player.py = (double) y + 0.5;
}

static void	set_playerangle(t_game *game, char look)
{
	double	plane_len;

	if (look == 'E')
		game->player.angle = 0;
	else if (look == 'S')
		game->player.angle = M_PI / 2;
	else if (look == 'W')
		game->player.angle = M_PI;
	else if (look == 'N')
		game->player.angle = 3 * M_PI / 2;
	game->player.dirX = cos(game->player.angle);
	game->player.dirY = sin(game->player.angle);
	plane_len = tan(FOV / 2.0);
	game->player.planeX = -game->player.dirY * plane_len;
	game->player.planeY = game->player.dirX * plane_len;
}

void	find_player(t_game *game)
{
	int		x;
	int		y;
	char	**map;
	
	if (!game)
		return ;
	map = game->file->map;
	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == 'N' || map[x][y] == 'S'
				|| map[x][y] == 'E' || map[x][y] == 'W')
			{
				set_playerpos(game, x, y);
				set_playerangle(game, map[x][y]);
				return ;
			}
			y++;
		}
		x++;
	}
}
