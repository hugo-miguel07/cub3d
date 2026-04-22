/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating_coordinates.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:15:11 by antabord          #+#    #+#             */
/*   Updated: 2026/04/22 13:12:45 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    checking_paths(s_file *file)
{
    int fd;

    fd = -1;
    fd = open(file->NO_texture, O_RDONLY);
    if (fd == -1)
        exit_check(INVALID_NOTEXTURE_PATH, file);
    fd = open(file->SO_texture, O_RDONLY);
    if (fd == -1)
        exit_check(INVALID_SOTEXTURE_PATH, file);
    fd = open(file->EA_texture, O_RDONLY);
    if (fd == -1)
        exit_check(INVALID_EATEXTURE_PATH, file);
    fd = open(file->WE_texture, O_RDONLY);
    if (fd == -1)
        exit_check(INVALID_WETEXTURE_PATH, file);
}

static void checking_coordinates_part2(s_file *file)
{
    char *sub;
    char *ptr1;
    char *ptr2;

    ptr1 = file->F_color;
    ptr2 = file->C_color;
    while (*ptr1)
    {        
        sub = ft_substr(ptr1, 0, (ft_strchr(ptr1, ',') - ptr1));
        if (!sub || ft_atoi(sub) > 255 || ft_atoi(sub) < 0)
        {
            free(sub);
            exit_check(INVALID_COLOR_COORDINATES);
        }
        ptr1 = sub;
        free(sub);
    }
    while (*ptr2)
    {        
        sub = ft_substr(ptr2, 0, (ft_strchr(ptr2, ',') - ptr2));
        if (!sub || ft_atoi(sub) > 255 || ft_atoi(sub) < 0)
        {
            free(sub);
            exit_check(INVALID_COLOR_COORDINATES);
        }
        ptr2 = sub;
        free(sub);
    }
}

void    checking_coordinates(s_file *files)
{
    char *ptr1;
    char *ptr2;
    int comma;

    comma = 0;
    ptr1 = files->F_color[1];
    ptr2 = files->C_color[1];
    while (*ptr1)
    {
        if (ptr1 == ',')
            comma++;
        ptr1++;
    }
    if (comma != 3)
        exit_check(INVALID_COLOR_COORDINATES, files);
    comma = 0;
    while (*ptr2)
    {
        if (ptr2 == ',')
            comma++;
        ptr2++;
    }
    if (comma != 3)
        exit_check(INVALID_COLOR_COORDINATES, files);
    checking_coordinates_part2(files);
}
