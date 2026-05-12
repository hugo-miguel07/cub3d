/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 12:30:55 by htavares          #+#    #+#             */
/*   Updated: 2026/05/12 13:14:19 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_player(t_game *game)
{
	int		x;
	int		y;
	char	**map;
	
	if (!game)
		return ;
	map = game->file->map;
	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == 'N' || map[x][y] == 'S'
				|| map[x][y] == 'E' || map[x][y] == 'W')
			{
				game->player.px = (double) x + 0.5;
				game->player.py = (double) y + 0.5;
				return ;
			}
			y++;
		}
		x++;
	}
}
