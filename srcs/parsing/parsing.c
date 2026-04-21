/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:57:30 by htavares          #+#    #+#             */
/*   Updated: 2026/04/21 15:31:40 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

s_file    parsing(s_file *file, char **av)
{
    int fd;

    fd = checking_cubfile(av[1]);
    checking_file(fd, file);
    checking_paths(file);
    checking_coordinates(file);
    checking_map(av[1]);
    return *file;
}