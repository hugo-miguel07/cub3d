/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:57:19 by htavares          #+#    #+#             */
/*   Updated: 2026/04/20 17:45:18 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_game_variables(t_game *game, s_file *file)
{
	t_point	player;

	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	player = find_player(file->map);
	if (player.x == -1 || player.y == -1)
		return (mlx_destroy_display(game->mlx), free(game->mlx), 0);
	game->player = player;
	game->img_wall = NULL;
	game->win_w = WIN_W;
	game->win_h = WIN_H;
	game->win = mlx_new_window(game->mlx, game->win_w,
			game->win_h, "cub3d");
	if (!game->win)
		return (mlx_destroy_display(game->mlx), free(game->mlx), 0);
	game->map = file->map;
	return (1);
}

int	exec(s_file *gamefile)
{
	t_game	*game;
	
	game = malloc(sizeof(t_game));
	if (!game)
		return (0);
	if (!init_game_variables(game ,gamefile))
		return (0);
	return (1);
}
