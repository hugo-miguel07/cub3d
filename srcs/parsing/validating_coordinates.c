/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating_coordinates.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:15:11 by antabord          #+#    #+#             */
/*   Updated: 2026/04/21 15:38:08 by antabord         ###   ########.fr       */
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

void    checking_coordinates(s_file *files)
{
    char *ptr1;
    char *ptr2;
    

    ptr1 = files->F_color[1];
    ptr2 = files->C_color[1];
    while (*ptr1)
    {
        ptr1++;
        if ((*ptr1 > '9' || *ptr2 < '0') ||)
        
    }
}