/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:22:56 by antabord          #+#    #+#             */
/*   Updated: 2026/04/24 15:32:49 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void flood_fill(s_file *file, char **map, int y, int x)
{
    if (y < 0 || !map[y] || x < 0 || x >= (int)ft_strlen(map[y]))
        return (free_arr(map, map_size(map)), exit_check(INVALID_WALLS, file));
    if (map[y][x] == 'V' || map[y][x] == '1')
        return ;
    if (map[y][x] == ' ' || map[y][x] == '\t')
        return (free_arr(map, map_size(map)), exit_check(INVALID_WALLS, file));
    map[y][x] = 'V';
    flood_fill(file, map, y + 1, x);
    flood_fill(file, map, y - 1, x);
    flood_fill(file, map, y, x + 1);
    flood_fill(file, map, y, x - 1);
}

void player_pos(s_file *file, char **cpy)
{
    int x;
    int y;

    y = 0;
    while (cpy[y])
    {
        x = 0;
        while(cpy[y][x])
        {
            if (cpy[y][x] == 'N' || cpy[y][x] == 'S' || cpy[y][x] == 'W' || cpy[y][x] == 'E')
                flood_fill(file, cpy, y, x);
            x++;
        }
        y++;
    }
}
