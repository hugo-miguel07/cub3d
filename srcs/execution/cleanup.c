/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:11:32 by htavares          #+#    #+#             */
/*   Updated: 2026/04/21 17:08:03 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	freemap(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
	map = NULL;
}

void	cleanup_file(s_file gamefile)
{
	if (gamefile.C_color)
		free(gamefile.C_color);
	if (gamefile.F_color)
		free(gamefile.F_color);
	if (gamefile.EA_texture)
		free(gamefile.EA_texture);
	if (gamefile.NO_texture)
		free(gamefile.NO_texture);
	if (gamefile.WE_texture)
		free(gamefile.WE_texture);
	if (gamefile.SO_texture)
		free(gamefile.SO_texture);
	gamefile.C_color = NULL;
	gamefile.F_color = NULL;
	gamefile.EA_texture = NULL;
	gamefile.NO_texture = NULL;
	gamefile.WE_texture = NULL;
	gamefile.SO_texture = NULL;
}

void	cleanup_game(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->map)
		freemap(game->map);
	game->map = NULL;
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
}
