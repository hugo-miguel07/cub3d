/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 12:09:35 by htavares          #+#    #+#             */
/*   Updated: 2026/05/20 14:20:09 by htavares         ###   ########.fr       */
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

static void	free_pair(char *pair[2])
{
	if (!pair)
		return ;
	if (pair[0])
	{
		free(pair[0]);
		pair[0] = NULL;
	}
	if (pair[1])
	{
		free(pair[1]);
		pair[1] = NULL;
	}
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
	free_pair(file->C_color);
	free_pair(file->F_color);
	free_pair(file->NO_texture);
	free_pair(file->WE_texture);
	free_pair(file->SO_texture);
	free_pair(file->EA_texture);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->zbuffer)
		free(game->zbuffer);
	if (game->frame)
		cleanup_frame(game);
	destroy_textures(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->file)
		cleanup_file(game->file);
	game->zbuffer = NULL;
	game->frame = NULL;
	game->win = NULL;
	game->mlx = NULL;
	game->file = NULL;
}
