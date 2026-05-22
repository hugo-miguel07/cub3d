/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:57:30 by htavares          #+#    #+#             */
/*   Updated: 2026/05/22 12:28:41 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_file	parsing(t_file *file, char **av)
{
	int	fd;

	fd = checking_cubfile(av[1]);
	if (fd == -1 || !checking_file(fd, file) || !checking_paths(file)
		|| !checking_rgb(file) || !checking_chars_n_walls(file, file->map)
		|| !texture_validation(file))
	{
		if (fd != -1)
			close(fd);
		cleanup(file);
		exit(1);
	}
	close(fd);
	map_cpy(file);
	return (*file);
}
