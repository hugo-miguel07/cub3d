/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:26:23 by antabord          #+#    #+#             */
/*   Updated: 2026/04/20 17:50:39 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char     *get_value(char *tmp)
{
    while (*tmp == ' ' || *tmp == '\t')
        tmp++;
    return tmp;
}

static void filling_struct_part2(char *tmp, char *id, s_file *file)
{
    if (!ft_strncmp(id, "F", 1))
    {
        file->F_color[0] = id;
        file->F_color[1] = get_value(tmp);
    }
    else if (!ft_strncmp(id, "C", 1))
    {
        file->C_color[0] = id;
        file->C_color[1] = get_value(tmp);
    }
    else
        exit_check(INVALID_ID);
}

void    filling_struct_part1(char *tmp, char *id, s_file *file)
{
    if (!ft_strncmp(id, "NO", 2))
    {
        file->NO_texture[0] = id;
        file->NO_texture[1] = get_value(tmp);
    }
    else if (!ft_strncmp(id, "SO", 2))
    {
        file->SO_texture[0] = id;
        file->SO_texture[1] = get_value(tmp);
    }
    else if (!ft_strncmp(id, "WE", 2))
    {
        file->WE_texture[0] = id;
        file->WE_texture[1] = get_value(tmp);
    }
    else if (!ft_strncmp(id, "EA", 2))
    {
        file->EA_texture[0] = id;
        file->EA_texture[1] = get_value(tmp);
    }
    else
        filling_struct_part2(tmp, id, file);
}