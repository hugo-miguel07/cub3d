/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:35:38 by antabord          #+#    #+#             */
/*   Updated: 2026/04/23 15:02:13 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int  valid_chars(char c)
{
    if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
        return 0;
    return 1;
}

static void checking_chars(s_file *file, char **map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (!valid_chars(map[i][j]))
                exit_check(INVALID_MAP_CHAR, file);
            j++;
        }
        i++;
    }
}

static void checking_char_disposition(s_file *file, t_map_parse *map_parse, char **map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (map[i])
    {
        j = 0;
        while (map[i])
        {
            if (map[i][j] == 'N')
                map_parse->N++;
            if (map[i][j] == 'S')
                map_parse->S++;
            if (map[i][j] == 'E')
                map_parse->E++;
            if (map[i][j] == 'W')
                map_parse->E++;
        }
    }
    if (map_parse->N != 1 || map_parse->S != 1 || map_parse->E != 1 || map_parse->W != 1)
        exit_check(INVALID_MAP_CHAR, file);
}

void    checking_map(s_file *file)
{
    t_map_parse map_parse;

    ft_memset(&map_parse, 0, sizeof(t_map_parse));
    checking_chars(file, file->map);
    checking_disposition(file, &map_parse, file->map);
}

