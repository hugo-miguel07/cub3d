/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 00:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/05/22 12:28:41 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_testfile(t_file *file)
{
	int	mapsize;
	int	i;
	int	j;

	mapsize = 10;
	file->map = ft_calloc(mapsize + 1, sizeof(char *));
	file->f_color = ft_calloc(3, sizeof(char *));
	file->c_color = ft_calloc(3, sizeof(char *));
	file->ea_texture = ft_calloc(3, sizeof(char *));
	file->we_texture = ft_calloc(3, sizeof(char *));
	file->so_texture = ft_calloc(3, sizeof(char *));
	file->no_texture = ft_calloc(3, sizeof(char *));
	i = 0;
	while (i < mapsize)
	{
		file->map[i] = ft_calloc(mapsize + 1, sizeof(char));
		j = 0;
		while (j < mapsize)
		{
			if (i == 0 || i == mapsize - 1 || j == 0 || j == mapsize - 1)
				file->map[i][j] = '1';
			else
				file->map[i][j] = '0';
			j++;
		}
		file->map[i][j] = '\0';
		i++;
	}
	file->map[i] = NULL;
	file->map[mapsize / 2][mapsize / 2] = 'N';
	file->f_color[0] = ft_strdup("F");
	file->f_color[1] = ft_strdup("113,115,102");
	file->f_color[2] = NULL;
	file->c_color[0] = ft_strdup("C");
	file->c_color[1] = ft_strdup("135,206,235");
	file->c_color[2] = NULL;
	file->no_texture[0] = ft_strdup("NO");
	file->no_texture[1] = ft_strdup("../imgs/Wall1.xpm");
	file->no_texture[2] = NULL;
	file->so_texture[0] = ft_strdup("SO");
	file->so_texture[1] = ft_strdup("../imgs/Wall2.xpm");
	file->so_texture[2] = NULL;
	file->we_texture[0] = ft_strdup("WE");
	file->we_texture[1] = ft_strdup("../imgs/Wall3.xpm");
	file->we_texture[2] = NULL;
	file->ea_texture[0] = ft_strdup("EA");
	file->ea_texture[1] = ft_strdup("../imgs/Wall4.xpm");
	file->ea_texture[2] = NULL;
	file->fill_counter = 6;
}

int	main(void)
{
	t_file	file;

	ft_bzero(&file, sizeof(file));
	setup_testfile(&file);
	if (!exec(&file))
		return (1);
	return (0);
}
