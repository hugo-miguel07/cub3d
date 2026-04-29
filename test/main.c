/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 00:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/04/29 00:00:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static const char	*error_message(enum exit_code code)
{
	if (code == INVALID_NUMBER_ARGS)
		return ("ERROR: invalid number of args");
	if (code == MALLOC_ERR)
		return ("ERROR: malloc");
	if (code == FILE_DOENST_EXIST)
		return ("ERROR: file doesn't exist");
	if (code == NO_READING_PERM)
		return ("ERROR: invalid file permissions");
	if (code == NON_PRINTABLE_CHARS)
		return ("ERROR: file name has non-printable chars");
	if (code == INVALID_TYPE_FILE)
		return ("ERROR: file must end with .cub");
	if (code == EMPTY_FILE)
		return ("ERROR: file is empty");
	if (code == INVALID_ID)
		return ("ERROR: invalid id");
	if (code == INVALID_NOTEXTURE_PATH)
		return ("ERROR: invalid NO texture path");
	if (code == INVALID_SOTEXTURE_PATH)
		return ("ERROR: invalid SO texture path");
	if (code == INVALID_EATEXTURE_PATH)
		return ("ERROR: invalid EA texture path");
	if (code == INVALID_WETEXTURE_PATH)
		return ("ERROR: invalid WE texture path");
	if (code == INVALID_COLOR_COORDINATES)
		return ("ERROR: invalid color coordinates");
	if (code == EMPTY_LINE_INSIDE_MAP)
		return ("ERROR: empty line inside map");
	if (code == INVALID_MAP_CHAR)
		return ("ERROR: invalid map char");
	if (code == INVALID_WALLS)
		return ("ERROR: invalid walls");
	if (code == INVALID_PLAYER_SPAWN)
		return ("ERROR: invalid player spawn");
	return ("ERROR: unknown parsing error");
}

void	free_arr(char **arr, int index)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	if (index <= 0)
	{
		while (arr[i])
			free(arr[i++]);
	}
	else
	{
		while (i < index && arr[i])
			free(arr[i++]);
	}
	free(arr);
}

static void	cleanup_file(s_file *file)
{
	free_arr(file->NO_texture, 0);
	free_arr(file->SO_texture, 0);
	free_arr(file->WE_texture, 0);
	free_arr(file->EA_texture, 0);
	free_arr(file->F_color, 0);
	free_arr(file->C_color, 0);
	free_arr(file->map, 0);
}

static void	init_file(s_file *file)
{
	file->NO_texture = ft_calloc(2, sizeof(char *));
	file->SO_texture = ft_calloc(2, sizeof(char *));
	file->WE_texture = ft_calloc(2, sizeof(char *));
	file->EA_texture = ft_calloc(2, sizeof(char *));
	file->F_color = ft_calloc(2, sizeof(char *));
	file->C_color = ft_calloc(2, sizeof(char *));
	if (!file->NO_texture || !file->SO_texture || !file->WE_texture
		|| !file->EA_texture || !file->F_color || !file->C_color)
		exit_check(MALLOC_ERR, file);
}

void	exit_check(enum exit_code code, s_file *file)
{
	fprintf(stderr, "%s\n", error_message(code));
	if (file)
		cleanup_file(file);
	exit(EXIT_FAILURE);
}

static void	print_pair(const char *label, char **pair)
{
	if (!pair || !pair[1])
	{
		printf("%s: (missing)\n", label);
		return ;
	}
	printf("%s: %s\n", label, pair[1]);
}

static void	print_map(char **map)
{
	int	y;

	printf("Map:\n");
	y = 0;
	while (map && map[y])
	{
		printf("%02d | %s\n", y, map[y]);
		y++;
	}
}

int	main(int ac, char **av)
{
	s_file	file;

	if (ac != 2)
		exit_check(INVALID_NUMBER_ARGS, NULL);
	ft_memset(&file, 0, sizeof(file));
	init_file(&file);
	file = parsing(&file, av);
	print_pair("NO", file.NO_texture);
	print_pair("SO", file.SO_texture);
	print_pair("WE", file.WE_texture);
	print_pair("EA", file.EA_texture);
	print_pair("F", file.F_color);
	print_pair("C", file.C_color);
	printf("Player count: %d\n", file.player);
	printf("Map size: %d\n", map_size(file.map));
	print_map(file.map);
	cleanup_file(&file);
	return (0);
}