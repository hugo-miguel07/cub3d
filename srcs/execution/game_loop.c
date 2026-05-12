/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:01:02 by htavares          #+#    #+#             */
/*   Updated: 2026/05/12 15:39:20 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_game *game)
{
    cleanup_game(game);
    exit(0);
    return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
    {
        cleanup_game(game);
        exit(0);
    }
	return (0);
}

int	render(t_game *game)
{
	if (!game || !game->frame || !game->mlx || !game->win || !game->zbuffer)
		return (0);
	draw_scene(game);
	mlx_put_image_to_window(game->mlx, game->win, game->frame->img_mlx, 0, 0);
	return (1);
}

void	game_loop(t_game *game)
{
	mlx_hook(game->win, 2, 1L<<0, (int (*)())key_press, game);
	mlx_hook(game->win, 17, 0, (int (*)())close_window, game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_loop(game->mlx);
}
