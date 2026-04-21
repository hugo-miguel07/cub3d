/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:57:19 by htavares          #+#    #+#             */
/*   Updated: 2026/04/21 17:11:21 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	run_game(t_game *game)
{
	
}

int	exec(s_file gamefile)
{
	t_game	*game;
	
	game = malloc(sizeof(t_game));
	if (!game)
		return (0);
	if (!init_game_variables(game ,gamefile))
		return (cleanup_game(game), 0);
	run_game(game);
	cleanup_game(game);
	return (1);
}
