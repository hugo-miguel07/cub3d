/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating_coordinates.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:15:11 by antabord          #+#    #+#             */
/*   Updated: 2026/04/23 14:28:36 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void skip_spaces(char **ptr)
{
    while (**ptr == ' ' || **ptr == '\t')
        (*ptr)++;
}

void    checking_paths(s_file *file)
{
    int fd;

    fd = open(file->NO_texture[1], O_RDONLY);
    if (fd == -1)
        exit_check(INVALID_NOTEXTURE_PATH, file);
    close(fd);
    fd = open(file->SO_texture[1], O_RDONLY);
    if (fd == -1)
        exit_check(INVALID_SOTEXTURE_PATH, file);
    close(fd);
    fd = open(file->EA_texture[1], O_RDONLY);
    if (fd == -1)
        exit_check(INVALID_EATEXTURE_PATH, file);
    close(fd);
    fd = open(file->WE_texture[1], O_RDONLY);
    if (fd == -1)
        exit_check(INVALID_WETEXTURE_PATH, file);
    if (!file->C_color || !file->F_color || !file->C_color[1] || !file->F_color[1])
        exit_check(INVALID_COLOR_COORDINATES, file);
    close(fd);
}

static void    parse_commas(s_file *files, char *ptr)
{
    int commas;
    int nbrs;

    commas = 0;
    nbrs = 0;
    while (*ptr)
    {
        if (*ptr == ',')
        {
            if (nbrs > 3 || nbrs == 0)
            exit_check(INVALID_COLOR_COORDINATES, files);
            nbrs = 0;
            commas++;
            skip_spaces(&ptr);
        }
        else if (ft_isdigit(*ptr))
        {
            ptr++;
            nbrs++;
        }
        else
            break;
    }
    if (commas != 2 || nbrs > 3 || nbrs == 0 || *ptr != '\0')
        exit_check(INVALID_COLOR_COORDINATES, files);
}

static void     parse_coordinates(s_file *files, char *ptr)
{
    char *comma;
    int block_nbr;
    
    block_nbr = 0;
    while (*ptr)
    {
        if (block_nbr < 2)
        {
            skip_spaces(&ptr);
            comma = ft_strchr(ptr, ',');
            if (ft_atoi(ptr) > 255 || ft_atoi(ptr) < 0)
                exit_check(INVALID_COLOR_COORDINATES, files);
            block_nbr++;
            ptr = comma + 1;
        }
        else
        {
            skip_spaces(&ptr);
            if (ft_atoi(ptr) > 255 || ft_atoi(ptr) < 0)
                exit_check(INVALID_COLOR_COORDINATES, files);
            ptr += ft_strlen(ptr);
            break;
        }
    }
}

void    checking_rgb(s_file *files)
{
    parse_commas(files, files->F_color[1]);
    parse_commas(files, files->C_color[1]);
    parse_coordinates(files, files->F_color[1]);
    parse_coordinates(files, files->C_color[1]);
}
