/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 10:22:39 by htavares          #+#    #+#             */
/*   Updated: 2026/05/21 18:23:21 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	exit_check2(enum exit_code code, s_file *file)
{
	(void)file;
	if (code ==  INVALID_NOTEXTURE_PATH)
        fprintf(stderr, "ERROR: INVALID NO texture\n");
    else if (code ==  INVALID_SOTEXTURE_PATH)
        fprintf(stderr, "ERROR: INVALID SO texture\n");
    else if (code ==  INVALID_EATEXTURE_PATH)
        fprintf(stderr, "ERROR: INVALID EA texture\n");
    else if (code ==  INVALID_WETEXTURE_PATH)
        fprintf(stderr, "ERROR: INVALID WE texture\n");
    else if (code ==  INVALID_COLOR_COORDINATES)
        fprintf(stderr, "ERROR: INVALID color coordinates\n");
    else if (code ==  EMPTY_LINE_INSIDE_MAP)
        fprintf(stderr, "ERROR: Empty line inside map\n");
    else if (code ==  INVALID_MAP_CHAR)
        fprintf(stderr, "ERROR: Invalid map char\n");
    else if (code ==  INVALID_WALLS)
        fprintf(stderr, "ERROR: Invalid walls\n");
    else if (code ==  INVALID_PLAYER_SPAWN)
        fprintf(stderr, "ERROR: Invalid spawn\n");
}

void    exit_check(enum exit_code code, s_file *file)
{
    if (code ==  INVALID_NUMBER_ARGS)
        fprintf(stderr, "ERROR: Inavlid number of args\n");
    else if (code ==  MALLOC_ERR)
        fprintf(stderr, "ERROR: malloc\n");
    else if (code ==  FILE_DOENST_EXIST)
        fprintf(stderr, "ERROR: File doesn't exixt\n");
    else if (code ==  NO_READING_PERM)
        fprintf(stderr, "ERROR: Invalid file permissions\n");
    else if (code ==  NON_PRINTABLE_CHARS)
        fprintf(stderr, "ERROR: File name cnat have non-printable chars\n");
    else if (code ==  INVALID_TYPE_FILE)
        fprintf(stderr, "ERROR: File must terminate with .cub\n");
    else if (code ==  EMPTY_FILE)
        fprintf(stderr, "ERROR: File is empty\n");
    else if (code ==  INVALID_ID)
        fprintf(stderr, "ERROR: INVALID ID\n");
	else
		exit_check2(code, file);
}

static void	cleanup2(s_file *file)
{
	if (file->WE_texture[1])
        free(file->WE_texture[1]);
    if (file->EA_texture[0])
        free(file->EA_texture[0]);
    if (file->EA_texture[1])
        free(file->EA_texture[1]);
    if (file->F_color[0])
        free(file->F_color[0]);
    if (file->F_color[1])
        free(file->F_color[1]);
    if (file->C_color[0])
        free(file->C_color[0]);
    if (file->C_color[1])
        free(file->C_color[1]);
    if (file->map)
        free_arr(file->map, 0);
}

void    cleanup(s_file *file)
{
    if (!file)
        exit(1);
    if (file->NO_texture[0])
        free(file->NO_texture[0]);
    if (file->NO_texture[1])
        free(file->NO_texture[1]);
    if (file->SO_texture[0])
        free(file->SO_texture[0]);
    if (file->SO_texture[1])
        free(file->SO_texture[1]);
    if (file->WE_texture[0])
        free(file->WE_texture[0]);
	else
		cleanup2(file);
}

int free_arr(char **arr, int index)
{
    int i;

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
