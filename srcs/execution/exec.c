/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:57:19 by htavares          #+#    #+#             */
/*   Updated: 2026/05/13 12:58:14 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_init(t_game *game, s_file *file)
{
	game->mlx = NULL;
	game->win = NULL;
	game->file = file;
	game->player.px = -1.0;
	game->player.py = -1.0;
	game->player.angle = 0.0;
	game->player.dirX = 0.0;
	game->player.dirY = 0.0;
	game->player.planeX = 0.0;
	game->player.planeY = 0.0;
	game ->frame = NULL;
	game->zbuffer = NULL;
}

static int	start_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, WIDTHW, HEIGHTW, "cub3d");
	if (!game->win)
		return (mlx_destroy_display(game->mlx), free(game->mlx), 0);
	find_player(game);
	return (1);
}

int	exec(s_file *file)
{
	t_game game;

	if (!file)
		return (0);
	game_init(&game, file);
	if (!start_mlx(&game))
		return (0);
	if (!create_frame(&game))
		return (cleanup_game(&game), 0);
	if (!create_zbuffer(&game))
		return (cleanup_game(&game), 0);
	game_loop(&game);
	cleanup_game(&game);
	return (1);
}
