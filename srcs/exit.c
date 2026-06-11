/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 10:22:39 by htavares          #+#    #+#             */
/*   Updated: 2026/05/22 12:55:55 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	exit_check2(enum e_exit_code code, t_file *file)
{
	(void)file;
	if (code == invalid_notexture_path)
		fprintf(stderr, "ERROR: INVALID NO texture\n");
	else if (code == invalid_sotexture_path)
		fprintf(stderr, "ERROR: INVALID SO texture\n");
	else if (code == invalid_eatexture_path)
		fprintf(stderr, "ERROR: INVALID EA texture\n");
	else if (code == invalid_wetexture_path)
		fprintf(stderr, "ERROR: INVALID WE texture\n");
	else if (code == inavlid_colo_coordinates)
		fprintf(stderr, "ERROR: INVALID color coordinates\n");
	else if (code == empty_line_inside_map)
		fprintf(stderr, "ERROR: Empty line inside map\n");
	else if (code == invalid_map_char)
		fprintf(stderr, "ERROR: Invalid map char\n");
	else if (code == invalid_walls)
		fprintf(stderr, "ERROR: Invalid walls\n");
	else if (code == invalid_spawn)
		fprintf(stderr, "ERROR: Invalid spawn\n");
}

void	exit_check(enum e_exit_code code, t_file *file)
{
	if (code == invalid_number_args)
		fprintf(stderr, "ERROR: Inavlid number of args\n");
	else if (code == malloc_err)
		fprintf(stderr, "ERROR: malloc\n");
	else if (code == file_doesnt_exist)
		fprintf(stderr, "ERROR: File doesn't exixt\n");
	else if (code == invalid_file)
		fprintf(stderr, "ERROR: Invalid file\n");
	else if (code == non_printable_chars)
		fprintf(stderr, "ERROR: File name cnat have non-printable chars\n");
	else if (code == invalid_type_file)
		fprintf(stderr, "ERROR: File must terminate with .cub\n");
	else if (code == empty_file)
		fprintf(stderr, "ERROR: File is empty\n");
	else if (code == invalid_id)
		fprintf(stderr, "ERROR: INVALID ID\n");
	else if (code == invalid_map)
		fprintf(stderr, "ERROR: INVALID MAP\n");
	else
		exit_check2(code, file);
}

static void	cleanup2(t_file *file)
{
	if (file->we_texture[1])
		free(file->we_texture[1]);
	if (file->ea_texture[0])
		free(file->ea_texture[0]);
	if (file->ea_texture[1])
		free(file->ea_texture[1]);
	if (file->f_color[0])
		free(file->f_color[0]);
	if (file->f_color[1])
		free(file->f_color[1]);
	if (file->c_color[0])
		free(file->c_color[0]);
	if (file->c_color[1])
		free(file->c_color[1]);
	if (file->map)
		free_arr(file->map, 0);
}

void	cleanup(t_file *file)
{
	if (!file)
		exit(1);
	if (file->no_texture[0])
		free(file->no_texture[0]);
	if (file->no_texture[1])
		free(file->no_texture[1]);
	if (file->so_texture[0])
		free(file->so_texture[0]);
	if (file->so_texture[1])
		free(file->so_texture[1]);
	if (file->we_texture[0])
	{
		free(file->we_texture[0]);
	}
	cleanup2(file);
}

int	free_arr(char **arr, int index)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	if (!index)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
	}
	else
	{
		while (i < index)
		{
			if (arr[i])
				free(arr[i]);
			i++;
		}
	}
	free(arr);
	return (1);
}
