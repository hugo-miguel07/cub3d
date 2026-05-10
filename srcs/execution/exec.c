/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:57:19 by htavares          #+#    #+#             */
/*   Updated: 2026/05/10 13:28:24 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_init(t_game *game, s_file *file)
{
	game->mlx = NULL;
	game->win = NULL;
	game->file = file;
	game->player.px = 0;
	game->player.py = 0;
}

static int	start_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, WIDTHW, HEIGHTW, "cub3d");
	if (game->win)
		return (mlx_destroy_display(game->mlx), 0);
	return (1);
}

int	exec(s_file *file)
{
	t_game game;

	if (!file)
		return (0);
	game_init(&game, file);
	if (start_mlx(&game))
		return (0);
	return (1);
}
