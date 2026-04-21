/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:26:23 by antabord          #+#    #+#             */
/*   Updated: 2026/04/21 15:25:59 by antabord         ###   ########.fr       */
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
    if (!ft_strncmp(id, "EA", 2) && id[2] == '\0')
    {
        file->EA_texture[0] = ft_strdup(id);
        file->EA_texture[1] = ft_strdup(get_value(tmp));
        file->fill_counter++;
    }
    else if (!ft_strncmp(id, "F", 1) && id[1] == '\0')
    {
        file->F_color[0] = ft_strdup(id);
        file->F_color[1] = ft_strdup(get_value(tmp));
        file->fill_counter++;
    }
    else if (!ft_strncmp(id, "C", 1) && id[1] == '\0')
    {
        file->C_color[0] = ft_strdup(id);
        file->C_color[1] = ft_strdup(get_value(tmp));
        file->fill_counter++;
    }
    else
        exit_check(INVALID_ID, file);
}

void    filling_struct_part1(char *tmp, char *id, s_file *file)
{
    if (!ft_strncmp(id, "NO", 2) && id[2] == '\0')
    {
        file->NO_texture[0] = ft_strdup(id);
        file->NO_texture[1] = ft_strdup(get_value(tmp));
        file->fill_counter++;
    }
    else if (!ft_strncmp(id, "SO", 2) && id[2] == '\0')
    {
        file->SO_texture[0] = ft_strdup(id);
        file->SO_texture[1] = ft_strdup(get_value(tmp));
        file->fill_counter++;
    }
    else if (!ft_strncmp(id, "WE", 2) && id[2] == '\0')
    {
        file->WE_texture[0] = ft_strdup(id);
        file->WE_texture[1] = ft_strdup(get_value(tmp));
        file->fill_counter++;
    }
    else
        filling_struct_part2(tmp, id, file);
}

static int  map_size(char **map)
{
    int i;

    i = 0;
    if (!map)
        return 0;
    while (map[i])
        i++;
    return i;
}
void    filling_struct_part3(char *tmp, s_file *file)
{
    int len;
    int i;
    char **new_map;
    
    i = 0;
    len = map_size(file->map);
    new_map = malloc(sizeof(char *) * (len + 2));
    if (!new_map)
        exit_check(MALLOC_ERR, file);
    while (file->map && file->map[i])
    {
        new_map[i] = file->map[i];
        i++;
    }
    new_map[i] = ft_strdup(tmp);
    if (!new_map[i])
    {
        free(new_map);
        exit_check(MALLOC_ERR, file);
    }
    new_map[i + 1] = NULL;
    free(file->map);
    file->map = new_map;
}
