/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:25:43 by antabord          #+#    #+#             */
/*   Updated: 2026/04/23 14:16:53 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static char *get_line_update_buffer(char *tmp, char *buffer)
{
    char *start;

    if (!tmp)
        return NULL;
    start = ft_strchr(tmp, '\n');
    if (!start)
    {
        buffer[0] = '\0';
        return tmp;
    }
    *start = '\0';
    ft_memmove(buffer, start + 1, ft_strlen(start + 1) + 1);
    return tmp;
}

static int getting_id(char *tmp, s_file *file)
{
    char id[3];

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
        tmp++;
        filling_struct_part1(tmp, id, file);
    }
    else if (*tmp && file->fill_counter == 6)
    {
        filling_struct_part3(tmp, file);
        return 1;
    }
    else
        exit_check(INVALID_ID, file);
    return 0;
}

static char    *reading_file(int fd)
{
    int bytes_read;
    static char buffer[BUFFER_SIZE + 1];
    char *tmp;
    char *old_tmp;
    char *line;

    tmp = NULL;
    if (buffer[0])
    {
        tmp = ft_strjoin(NULL, buffer);
        buffer[0] = '\0';
    }
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        old_tmp = tmp;
        tmp = ft_strjoin(tmp, buffer);
        free(old_tmp);
        if (!tmp)
            break;
        if (ft_strchr(tmp, '\n'))
            break;
    }
    line = get_line_update_buffer(tmp, buffer);
    return line;
}

void    checking_file(int fd, s_file *file)
{
    char *line;
    char *ptr;
    int map_started;

    map_started = 0;
    while ((line = reading_file(fd)))
    {
        ptr = line;
        skip_spaces(&line);
        if (*line == '\0')
        {
            if (map_started == 1)
                exit_check(EMPTY_LINE_INSIDE_MAP, file);
            free(ptr);
            continue;
        }
        map_started = getting_id(line, file);
        free(ptr);
    }
    close(fd);
}

