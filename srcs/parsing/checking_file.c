/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:25:43 by antabord          #+#    #+#             */
/*   Updated: 2026/04/20 17:50:49 by antabord         ###   ########.fr       */
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
        return tmp;
    *start = '\0';
    buffer = start;
    return tmp;
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
        tmp++;
        filling_struct_part1(tmp, id, file);
    }
    else
        exit_check(INVALID_ID);
}

static char    *reading_file(int fd)
{
    int bytes_read;
    static char buffer[BUFFER_SIZE + 1];
    char *tmp;
    char *old_tmp;
    char *line;

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
        if (!tmp)
            break;
        free(old_tmp);
        if (ft_strchr(tmp, '\n'))
            break;
    }
    line = get_line_update_buffer(tmp, buffer);
    return line;
}

void    checking_file(int fd, s_file *file)
{
    char *line;

    while (line = reading_file(fd))
    {
        getting_id(line, file);
        free(line);
    }
    close(fd);

    
}

