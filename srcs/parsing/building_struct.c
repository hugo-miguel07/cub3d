/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:26:23 by antabord          #+#    #+#             */
/*   Updated: 2026/05/22 12:28:41 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*get_value(char *tmp)
{
	while (*tmp == '\n' || *tmp == ' ' || *tmp == '\t')
		tmp++;
	return (tmp);
}

static void	filling_struct_part2(char *tmp, char *id, t_file *file)
{
	if (!ft_strncmp(id, "EA", 2) && id[2] == '\0')
	{
		file->ea_texture[0] = ft_strdup(id);
		file->ea_texture[1] = ft_strdup(get_value(tmp));
		file->fill_counter++;
	}
	else if (!ft_strncmp(id, "F", 1) && id[1] == '\0')
	{
		file->f_color[0] = ft_strdup(id);
		file->f_color[1] = ft_strdup(get_value(tmp));
		file->fill_counter++;
	}
	else if (!ft_strncmp(id, "C", 1) && id[1] == '\0')
	{
		file->c_color[0] = ft_strdup(id);
		file->c_color[1] = ft_strdup(get_value(tmp));
		file->fill_counter++;
	}
	else
		return ;
}

void	filling_struct_part1(char *tmp, char *id, t_file *file)
{
	skip_spaces(&tmp);
	if (!ft_strncmp(id, "NO", 2) && id[2] == '\0')
	{
		file->no_texture[0] = ft_strdup(id);
		file->no_texture[1] = ft_strdup(get_value(tmp));
		file->fill_counter++;
	}
	else if (!ft_strncmp(id, "SO", 2) && id[2] == '\0')
	{
		file->so_texture[0] = ft_strdup(id);
		file->so_texture[1] = ft_strdup(get_value(tmp));
		file->fill_counter++;
	}
	else if (!ft_strncmp(id, "WE", 2) && id[2] == '\0')
	{
		file->we_texture[0] = ft_strdup(id);
		file->we_texture[1] = ft_strdup(get_value(tmp));
		file->fill_counter++;
	}
	else
		filling_struct_part2(tmp, id, file);
}

int	map_size(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return (0);
	while (map[i])
		i++;
	return (i);
}

void	filling_struct_part3(char *tmp, t_file *file)
{
	int		len;
	int		i;
	char	**new_map;

	i = 0;
	len = map_size(file->map);
	new_map = calloc((len + 2), sizeof(char *));
	if (!new_map)
		exit_check(malloc_err, file);
	while (file->map && file->map[i])
	{
		new_map[i] = file->map[i];
		i++;
	}
	new_map[i] = ft_strdup(tmp);
	if (!new_map[i])
	{
		free(new_map);
		exit_check(malloc_err, file);
	}
	new_map[i + 1] = NULL;
	free(file->map);
	file->map = new_map;
}

