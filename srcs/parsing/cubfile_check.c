/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubfile_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:13:32 by antabord          #+#    #+#             */
/*   Updated: 2026/05/22 12:55:39 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	checking_cubfile(char *av)
{
	int		fd;
	char	buffer;
	int		bytes_read;

	fd = -1;
	bytes_read = 0;
	if (!av)
		return (exit_check(file_doesnt_exist, NULL), -1);
	if (!ft_strrchr(av, '.') || ft_strncmp(ft_strrchr(av, '.'), ".cub", 5) != 0)
		return (exit_check(invalid_type_file, NULL), -1);
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (exit_check(invalid_file, NULL), -1);
	bytes_read = read(fd, &buffer, 1);
	close(fd);
	if (!bytes_read)
		return (exit_check(empty_file, NULL), -1);
	if (bytes_read == -1)
		return (exit_check(invalid_file, NULL), -1);
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (exit_check(invalid_file, NULL), -1);
	return (fd);
}
