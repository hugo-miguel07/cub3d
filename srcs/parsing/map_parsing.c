/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:35:38 by antabord          #+#    #+#             */
/*   Updated: 2026/04/23 18:08:33 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int  valid_chars(char c, s_file *file)
{
    if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
        return 0;
    if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
        file->player++;
    return 1;
}

void checking_chars_n_walls(s_file *file, char **map)
{
    int i;
    int j;
    int last;

    i = 0;
    j = 0;
    while (map[i])
    {
        j = 0;
        last = map_size()
        if (map[i][0] != '1')
            exit_check(INVALID_WALLS, file);
        while (map[i][j])
        {
            if (!valid_chars(map[i][j], file))
                exit_check(INVALID_MAP_CHAR, file);
            if (map[0][j] != '1' || map[map_size(map) - 1][j] != '1')
                exit_check(INVALID_WALLS, file);
            j++;
        }
        if (map[i][ft_strlen(map[i]) - 1] != '1')
            exit_check(INVALID_WALLS, file);
        i++;
    }
    if (file->player != 1)
        exit_check(INVALID_PLAYER_SPAWN, file);
}

