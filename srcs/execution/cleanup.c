/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 12:09:35 by htavares          #+#    #+#             */
/*   Updated: 2026/05/19 15:02:59 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_arr_exec(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

static void	cleanup_frame(t_game *game)
{
	if (!game || !game->frame)
		return ;
	if (game->frame->img_mlx)
		mlx_destroy_image(game->mlx, game->frame->img_mlx);
	free(game->frame);
}

void	cleanup_file(s_file *file)
{
	if (!file)
		return ;
	if (file->map)
		free_arr_exec(file->map);
	if (file->C_color)
		free_arr_exec(file->C_color);
	if (file->F_color)
		free_arr_exec(file->F_color);
	if (file->NO_texture)
		free_arr_exec(file->NO_texture);
	if (file->WE_texture)
		free_arr_exec(file->WE_texture);
	if (file->SO_texture)
		free_arr_exec(file->SO_texture);
	if (file->EA_texture)
		free_arr_exec(file->EA_texture);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->zbuffer)
	{
		free(game->zbuffer);
		game->zbuffer = NULL;
	}
	if (game->frame)
	{
		cleanup_frame(game);
		game->frame = NULL;
	}
	destroy_textures(game);
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	if (game->file)
		cleanup_file(game->file);
}
