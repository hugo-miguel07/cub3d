/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:25:43 by antabord          #+#    #+#             */
/*   Updated: 2026/04/20 16:09:58 by antabord         ###   ########.fr       */
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

static void    filling_struct_part1(char *tmp, char *id, s_file *file)
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

static void getting_id(char *tmp, s_file *file)
{
    char id[3];

    while (*tmp == ' ' || *tmp == '\t')
        tmp++;
    if (*tmp == 'N' || *tmp == 'S' || *tmp == 'W' || *tmp == 'E' || *tmp == 'F' || *tmp == 'C')
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
        filling_struct_part1(tmp, id, file);
    }
    else
        exit_check(INVALID_ID);
}

void    checking_file(int fd, s_file *file)
{
    int bytes_read;
    static char buffer[BUFFER_SIZE + 1];
    char *tmp;
    char *old_tmp;

    tmp = ft_calloc(1, 1);
    while (((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) && !ft_strchr(tmp, '\n'))
    {
        buffer[bytes_read] = '\0';
        old_tmp = tmp;
        tmp = ft_strjoin(tmp, buffer);
        if (!tmp)
        {
            free(old_tmp);
            break;
        }
        free(old_tmp);
    }
    getting_id(tmp, file);
    free(tmp);
    close(fd);
}

