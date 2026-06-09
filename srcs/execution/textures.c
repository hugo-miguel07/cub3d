/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:02:00 by htavares          #+#    #+#             */
/*   Updated: 2026/05/22 12:26:43 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_texture(t_texture *tex)
{
	tex->img_mlx = NULL;
	tex->pixels = NULL;
	tex->width = 0;
	tex->height = 0;
	tex->bits_per_pix = 0;
	tex->line_length = 0;
	tex->endian = 0;
}

static int	load_texture(t_game *game, t_texture *tex, char *path)
{
	init_texture(tex);
	if (!path)
		return (0);
	tex->img_mlx = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img_mlx)
		return (0);
	tex->pixels = mlx_get_data_addr(tex->img_mlx, &tex->bits_per_pix,
			&tex->line_length, &tex->endian);
	if (!tex->pixels)
	{
		mlx_destroy_image(game->mlx, tex->img_mlx);
		init_texture(tex);
		return (0);
	}
	return (1);
}

int	load_textures(t_game *game)
{
	if (!game || !game->file)
		return (0);
	if (!load_texture(game, &game->textures.no, game->file->no_texture[1]))
		return (0);
	if (!load_texture(game, &game->textures.so, game->file->so_texture[1]))
		return (destroy_textures(game), 0);
	if (!load_texture(game, &game->textures.we, game->file->we_texture[1]))
		return (destroy_textures(game), 0);
	if (!load_texture(game, &game->textures.ea, game->file->ea_texture[1]))
		return (destroy_textures(game), 0);
	return (1);
}

void	destroy_textures(t_game *game)
{
	if (!game || !game->mlx)
		return ;
	if (game->textures.no.img_mlx)
		mlx_destroy_image(game->mlx, game->textures.no.img_mlx);
	if (game->textures.so.img_mlx)
		mlx_destroy_image(game->mlx, game->textures.so.img_mlx);
	if (game->textures.we.img_mlx)
		mlx_destroy_image(game->mlx, game->textures.we.img_mlx);
	if (game->textures.ea.img_mlx)
		mlx_destroy_image(game->mlx, game->textures.ea.img_mlx);
	init_texture(&game->textures.no);
	init_texture(&game->textures.so);
	init_texture(&game->textures.we);
	init_texture(&game->textures.ea);
}
