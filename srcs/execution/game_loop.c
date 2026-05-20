/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:01:02 by htavares          #+#    #+#             */
/*   Updated: 2026/05/20 14:23:48 by htavares         ###   ########.fr       */
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
	if (keycode == 119)
		game->input.w = 1;
	else if (keycode == 115)
		game->input.s = 1;
	else if (keycode == 97)
		game->input.a = 1;
	else if (keycode == 100)
		game->input.d = 1;
	else if (keycode == 65361)
		game->input.left = 1;
	else if (keycode == 65363)
		game->input.right = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 119)
		game->input.w = 0;
	else if (keycode == 115)
		game->input.s = 0;
	else if (keycode == 97)
		game->input.a = 0;
	else if (keycode == 100)
		game->input.d = 0;
	else if (keycode == 65361)
		game->input.left = 0;
	else if (keycode == 65363)
		game->input.right = 0;
	return (0);
}

int	render(t_game *game)
{
	if (!game || !game->frame || !game->mlx || !game->win || !game->zbuffer)
		return (0);
	move_player(game);
	look_player(game);
	draw_scene(game);
	mlx_put_image_to_window(game->mlx, game->win, game->frame->img_mlx, 0, 0);
	return (1);
}

void	game_loop(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, (int (*)())key_press, game);
	mlx_hook(game->win, 3, 1L << 1, (int (*)())key_release, game);
	mlx_hook(game->win, 17, 0, (int (*)())close_window, game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_loop(game->mlx);
}
