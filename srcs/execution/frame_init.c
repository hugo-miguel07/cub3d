/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 13:18:10 by htavares          #+#    #+#             */
/*   Updated: 2026/05/12 14:53:01 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void init_frame(t_frame *frame)
{
	frame->img_mlx = NULL;
	frame->bits_per_pix = 0;
	frame->endian = 0;
	frame->height = 0;
	frame->width = 0;
	frame->line_length = 0;
	frame->pixels = NULL;
}

int	create_frame(t_game *game)
{
	if (!game)
		return (0);
	game->frame = malloc(sizeof(t_frame));
	if (!game->frame)
		return (0);
	init_frame(game->frame);
	game->frame->img_mlx = mlx_new_image(game->mlx, WIDTHW, HEIGHTW);
	if (!game->frame->img_mlx)
		return (free(game->frame), 0);
	game->frame->pixels = mlx_get_data_addr(game->frame->img_mlx, 
											&game->frame->bits_per_pix,
											&game->frame->line_length,
											&game->frame->endian);
	game->frame->width = WIDTHW;
	game->frame->height = HEIGHTW;
	return (1);
}
