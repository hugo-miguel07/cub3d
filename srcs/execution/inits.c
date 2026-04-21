/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:01:13 by htavares          #+#    #+#             */
/*   Updated: 2026/04/21 17:04:52 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_to_default(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->player.x = -1.0;
	game->player.y = -1.0;
	game->player.orientation = 0;
	game->win_w = WIN_W;
	game->win_h = WIN_H;
}

int	init_game_variables(t_game *game, s_file file)
{
	t_point	player;

	set_to_default(game);
	if (!file.map)
		return (0);
	game->map = file.map;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	player = find_player(game->map);
	if (player.x < 0.0 || player.y < 0.0)
		return (0);
	game->player = player;
	game->win = mlx_new_window(game->mlx, game->win_w,
			game->win_h, "cub3d");
	if (!game->win)
		return (0);
	return (1);
}
