/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:35:38 by antabord          #+#    #+#             */
/*   Updated: 2026/05/22 12:52:43 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	valid_chars(char c, t_file *file)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
		&& c != ' ')
		return (0);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		file->player++;
	return (1);
}

int	checking_chars_n_walls(t_file *file, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	file->player = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!valid_chars(map[i][j], file))
				return (exit_check(invalid_map_char, file), 0);
			j++;
		}
		i++;
	}
	if (file->player != 1)
		return (exit_check(invalid_spawn, file), 0);
	return (1);
}

static int	flood_rest(t_file *file, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
			{
				if (!flood_fill(file, map, y, x))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	map_cpy(t_file *file)
{
	char	**map_cpy;
	int		rows;
	int		i;
	int		j;

	i = -1;
	rows = map_size(file->map);
	map_cpy = malloc((rows + 1) * sizeof(char *));
	if (!map_cpy)
		return (exit_check(malloc_err, file), 0);
	while (file->map[++i])
	{
		j = -1;
		map_cpy[i] = malloc(ft_strlen(file->map[i]) + 1);
		if (!map_cpy[i])
			return (free_arr(map_cpy, i), exit_check(malloc_err, file), 0);
		while (file->map[i][++j])
			map_cpy[i][j] = file->map[i][j];
		map_cpy[i][j] = '\0';
	}
	map_cpy[i] = NULL;
	if (!player_pos(file, map_cpy) || !flood_rest(file, map_cpy)
		|| free_arr(map_cpy, rows))
		return (0);
	return (1);
}
