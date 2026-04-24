/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:57:30 by htavares          #+#    #+#             */
/*   Updated: 2026/04/24 12:17:31 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

s_file    parsing(s_file *file, char **av)
{
    int fd;

    fd = checking_cubfile(av[1]);
    checking_file(fd, file);
    checking_paths(file);
    checking_rgb(file);
    checking_chars_n_walls(file, file->map);
    map_cpy(file);
    return *file;
}