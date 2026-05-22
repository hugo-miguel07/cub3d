/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating_coordinates.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:15:11 by antabord          #+#    #+#             */
/*   Updated: 2026/05/22 12:52:35 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	skip_spaces(char **ptr)
{
	while (**ptr == ' ' || **ptr == '\t')
		(*ptr)++;
}

int	checking_paths(t_file *file)
{
	int		fd;
	char	buffer;

	fd = open(file->so_texture[1], O_RDONLY);
	if (fd == -1 || !read(fd, &buffer, 1))
		return (exit_check(invalid_sotexture_path, file), 0);
	close(fd);
	fd = open(file->no_texture[1], O_RDONLY);
	if (fd == -1 || !read(fd, &buffer, 1))
		return (exit_check(invalid_notexture_path, file), 0);
	close(fd);
	fd = open(file->ea_texture[1], O_RDONLY);
	if (fd == -1 || !read(fd, &buffer, 1))
		return (exit_check(invalid_eatexture_path, file), 0);
	close(fd);
	fd = open(file->we_texture[1], O_RDONLY);
	if (fd == -1 || !read(fd, &buffer, 1))
		return (exit_check(invalid_wetexture_path, file), 0);
	close(fd);
	if (!file->c_color[1] || !file->f_color[1])
		return (exit_check(inavlid_colo_coordinates, file), 0);
	return (1);
}

static int	parse_commas(t_file *files, char *ptr)
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
				return (exit_check(inavlid_colo_coordinates, files), 0);
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
		return (exit_check(inavlid_colo_coordinates, files), 0);
	return (1);
}

static int	parse_coordinates(t_file *files, char *ptr)
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
				return (exit_check(inavlid_colo_coordinates, files), 0);
			block_nbr++;
			ptr = comma + 1;
		}
		else
		{
			skip_spaces(&ptr);
			if (ft_atoi(ptr) > 255 || ft_atoi(ptr) < 0)
				return (exit_check(inavlid_colo_coordinates, files), 0);
			ptr += ft_strlen(ptr);
			break ;
		}
	}
	return (1);
}

int	checking_rgb(t_file *files)
{
	if (!parse_commas(files, files->f_color[1]) || !parse_commas(files,
			files->c_color[1]) || !parse_coordinates(files, files->f_color[1])
		|| !parse_coordinates(files, files->c_color[1]))
		return (0);
	return (1);
}
