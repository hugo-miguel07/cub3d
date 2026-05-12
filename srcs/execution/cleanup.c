/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 12:09:35 by htavares          #+#    #+#             */
/*   Updated: 2026/05/12 15:46:52 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cleanup_frame(t_game *game)
{
	if (!game)
		return ;
	if (game->frame->img_mlx)
		mlx_destroy_image(game->mlx, game->frame->img_mlx);
	free(game->frame);
}

void	cleanup_file(s_file *file)
{
	if (file->map)
		free(file->map);
	if (file->C_color)
		free(file->C_color);
	if (file->F_color)
		free(file->F_color);
	if (file->NO_texture)
		free(file->NO_texture);
	if (file->WE_texture)
		free(file->WE_texture);
	if (file->SO_texture)
		free(file->SO_texture);
	if (file->EA_texture)
		free(file->EA_texture);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->zbuffer)
		free(game->zbuffer);
	if (game->frame)
		cleanup_frame(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
