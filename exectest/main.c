/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 00:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/05/13 13:30:37 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_testfile(s_file *file)
{
	int	mapsize;
	int	i;
	int	j;

	mapsize = 10;
	file->map = ft_calloc(mapsize + 1, sizeof(char *));
	file->F_color = ft_calloc(2, sizeof(char *));
	file->C_color = ft_calloc(2, sizeof(char *));
	file->EA_texture = ft_calloc(2, sizeof(char *));
	file->WE_texture = ft_calloc(2, sizeof(char *));
	file->SO_texture = ft_calloc(2, sizeof(char *));
	file->NO_texture = ft_calloc(2, sizeof(char *));
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
	file->F_color[0] = ft_strdup("F");
	file->F_color[1] = ft_strdup("113,115,102");
	file->C_color[0] = ft_strdup("C");
	file->C_color[1] = ft_strdup("135,206,235");
	file->NO_texture[0] = ft_strdup("NO");
	file->NO_texture[1] = NULL;
	file->SO_texture[0] = ft_strdup("SO");
	file->SO_texture[1] = NULL;
	file->WE_texture[0] = ft_strdup("WE");
	file->WE_texture[1] = NULL;
	file->EA_texture[0] = ft_strdup("EA");
	file->EA_texture[1] = NULL;
	file->fill_counter = 6;
}

int	main(void)
{
	s_file	file;

	ft_bzero(&file, sizeof(file));
	setup_testfile(&file);
	if (!exec(&file))
		return (1);
	return (0);
}
