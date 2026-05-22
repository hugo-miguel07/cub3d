/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:25:43 by antabord          #+#    #+#             */
/*   Updated: 2026/05/22 13:00:58 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	texture_validation(t_file *file)
{
	if (ft_strlen(file->no_texture[1]) <= 5 || !ft_strrchr(file->no_texture[1],
			'.') || ft_strncmp(ft_strrchr(file->no_texture[1], '.'), ".xpm",
			5) != 0)
		return (exit_check(invalid_notexture_path, file), 0);
	if (ft_strlen(file->so_texture[1]) <= 5 || !ft_strrchr(file->so_texture[1],
			'.') || ft_strncmp(ft_strrchr(file->so_texture[1], '.'), ".xpm",
			5) != 0)
		return (exit_check(invalid_sotexture_path, file), 0);
	if (ft_strlen(file->we_texture[1]) <= 5 || !ft_strrchr(file->we_texture[1],
			'.') || ft_strncmp(ft_strrchr(file->we_texture[1], '.'), ".xpm",
			5) != 0)
		return (exit_check(invalid_wetexture_path, file), 0);
	if (ft_strlen(file->ea_texture[1]) <= 5 || !ft_strrchr(file->ea_texture[1],
			'.') || ft_strncmp(ft_strrchr(file->ea_texture[1], '.'), ".xpm",
			5) != 0)
		return (exit_check(invalid_eatexture_path, file), 0);
	return (1);
}

static char	*get_line_update_buffer(char *tmp, char *buffer)
{
	char	*start;

	if (!tmp)
		return (NULL);
	start = ft_strchr(tmp, '\n');
	if (!start)
	{
		buffer[0] = '\0';
		return (tmp);
	}
	*start = '\0';
	ft_memmove(buffer, start + 1, ft_strlen(start + 1) + 1);
	return (tmp);
}

static int	getting_id(char *tmp, t_file *file)
{
	char	id[3];

	if (*tmp == 'N' || *tmp == 'S' || *tmp == 'W' || *tmp == 'E' || *tmp == 'F'
		|| *tmp == 'C')
	{
		id[0] = *tmp;
		if (*tmp == 'F' || *tmp == 'C')
			id[1] = '\0';
		else
		{
			tmp++;
			id[1] = *tmp;
			id[2] = '\0';
		}
		tmp++;
		filling_struct_part1(tmp, id, file);
	}
	else if (*tmp && file->fill_counter == 6)
	{
		filling_struct_part3(tmp, file);
		return (1);
	}
	else
		return (-1);
	return (0);
}

static char	*reading_file(int fd)
{
	int			bytes_read;
	static char	buffer[BUFFER_SIZE + 1];
	char		*tmp;
	char		*old_tmp;

	tmp = NULL;
	if (buffer[0])
	{
		tmp = ft_strjoin(NULL, buffer);
		buffer[0] = '\0';
	}
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		old_tmp = tmp;
		tmp = ft_strjoin(tmp, buffer);
		free(old_tmp);
		if (!tmp || ft_strchr(tmp, '\n'))
			break ;
	}
	return (get_line_update_buffer(tmp, buffer));
}

int	checking_file(int fd, t_file *file)
{
	char	*raw;
	char	*trim;

	raw = reading_file(fd);
	while (raw)
	{
		trim = raw;
		skip_spaces(&trim);
		if (file->fill_counter < 6)
		{
			if (*trim == '\0')
			{
				free(raw);
				raw = reading_file(fd);
				continue ;
			}
			if (getting_id(trim, file) < 0)
				return (free(raw), exit_check(invalid_id, file), 0);
		}
		else
			filling_struct_part3(raw, file);
		free(raw);
		raw = reading_file(fd);
	}
	return (close(fd), 1);
}
