/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating_coordinates.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:15:11 by antabord          #+#    #+#             */
/*   Updated: 2026/05/21 18:11:05 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	skip_spaces(char **ptr)
{
	while (**ptr == ' ' || **ptr == '\t')
		(*ptr)++;
}

int	checking_paths(s_file *file)
{
	int		fd;
	char	buffer;

	fd = open(file->SO_texture[1], O_RDONLY);
	if (fd == -1 || !read(fd, &buffer, 1))
		return (exit_check(INVALID_SOTEXTURE_PATH, file), 0);
	close(fd);
	fd = open(file->NO_texture[1], O_RDONLY);
	if (fd == -1 || !read(fd, &buffer, 1))
		return (exit_check(INVALID_NOTEXTURE_PATH, file), 0);
	close(fd);
	fd = open(file->EA_texture[1], O_RDONLY);
	if (fd == -1 || !read(fd, &buffer, 1))
		return (exit_check(INVALID_EATEXTURE_PATH, file), 0);
	close(fd);
	fd = open(file->WE_texture[1], O_RDONLY);
	if (fd == -1 || !read(fd, &buffer, 1))
		return (exit_check(INVALID_WETEXTURE_PATH, file), 0);
	if (!file->C_color[1] || !file->F_color[1])
		return (exit_check(INVALID_COLOR_COORDINATES, file), 0);
	return (close(fd), 1);
}

static int	parse_commas(s_file *files, char *ptr)
{
	int	commas;
	int	nbrs;

	commas = 0;
	nbrs = 0;
	while (*ptr)
	{
		if (*ptr == ',')
		{
			if (nbrs > 3 || nbrs == 0)
				return (exit_check(INVALID_COLOR_COORDINATES, files), 0);
			nbrs = 0;
			commas++;
			skip_spaces(&ptr);
		}
		else if (ft_isdigit(*ptr))
			nbrs++;
		else
			break ;
		ptr++;
	}
	if (commas != 2 || nbrs > 3 || nbrs == 0 || *ptr != '\0')
		return (exit_check(INVALID_COLOR_COORDINATES, files), 0);
    return (1);
}

static int	parse_coordinates(s_file *files, char *ptr)
{
	char	*comma;
	int		block_nbr;

	block_nbr = 0;
	while (*ptr)
	{
		if (block_nbr < 2)
		{
			skip_spaces(&ptr);
			comma = ft_strchr(ptr, ',');
			if (ft_atoi(ptr) > 255 || ft_atoi(ptr) < 0)
				return (exit_check(INVALID_COLOR_COORDINATES, files), 0);
			block_nbr++;
			ptr = comma + 1;
		}
		else
		{
			skip_spaces(&ptr);
			if (ft_atoi(ptr) > 255 || ft_atoi(ptr) < 0)
				return (exit_check(INVALID_COLOR_COORDINATES, files), 0);
			ptr += ft_strlen(ptr);
			break ;
		}
	}
    return (1);
}

int	checking_rgb(s_file *files)
{
	if (!parse_commas(files, files->F_color[1]) || !parse_commas(files, files->C_color[1]) || !parse_coordinates(files, files->F_color[1]) || !parse_coordinates(files, files->C_color[1]))
        return (0);
    return (1);
}
