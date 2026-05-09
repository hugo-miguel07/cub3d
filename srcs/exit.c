#include "cub3d.h"

static void	cleanup_exit(s_file *file)
{
    if (!file)
        return ;
    if (file->NO_texture)
        free_arr(file->NO_texture, 0);
    if (file->SO_texture)
        free_arr(file->SO_texture, 0);
    if (file->WE_texture)
        free_arr(file->WE_texture, 0);
    if (file->EA_texture)
        free_arr(file->EA_texture, 0);
    if (file->F_color)
        free_arr(file->F_color, 0);
    if (file->C_color)
        free_arr(file->C_color, 0);
    if (file->map)
        free_arr(file->map, 0);
}

void	exit_check(enum exit_code code, s_file *file)
{
    if (code == INVALID_NUMBER_ARGS)
        fprintf(stderr, "ERROR: Invalid number of args\n");
    else if (code == MALLOC_ERR)
        fprintf(stderr, "ERROR: malloc\n");
    else if (code == FILE_DOENST_EXIST)
        fprintf(stderr, "ERROR: File doesn't exist\n");
    else if (code == NO_READING_PERM)
        fprintf(stderr, "ERROR: Invalid file permissions\n");
    else if (code == NON_PRINTABLE_CHARS)
        fprintf(stderr, "ERROR: File name cannot have non-printable chars\n");
    else if (code == INVALID_TYPE_FILE)
        fprintf(stderr, "ERROR: File must terminate with .cub\n");
    else if (code == EMPTY_FILE)
        fprintf(stderr, "ERROR: File is empty\n");
    else if (code == INVALID_ID)
        fprintf(stderr, "ERROR: INVALID ID\n");
    else if (code == INVALID_NOTEXTURE_PATH)
        fprintf(stderr, "ERROR: INVALID NO texture path\n");
    else if (code == INVALID_SOTEXTURE_PATH)
        fprintf(stderr, "ERROR: INVALID SO texture path\n");
    else if (code == INVALID_EATEXTURE_PATH)
        fprintf(stderr, "ERROR: INVALID EA texture path\n");
    else if (code == INVALID_WETEXTURE_PATH)
        fprintf(stderr, "ERROR: INVALID WE texture path\n");
    else if (code == INVALID_COLOR_COORDINATES)
        fprintf(stderr, "ERROR: INVALID color coordinates\n");
    else if (code == EMPTY_LINE_INSIDE_MAP)
        fprintf(stderr, "ERROR: Empty line inside map\n");
    else if (code == INVALID_MAP_CHAR)
        fprintf(stderr, "ERROR: Invalid map char\n");
    else if (code == INVALID_WALLS)
        fprintf(stderr, "ERROR: Invalid walls\n");
    else if (code == INVALID_PLAYER_SPAWN)
        fprintf(stderr, "ERROR: Invalid spawn\n");

    cleanup_exit(file);
    exit(EXIT_FAILURE);
}

void free_arr(char **arr, int index)
{
    int i;

    i = -1;
    if (!index)
    {
        while (arr[++i])
            free(arr[i]);
    }
    else
    {
        while (++i < index)
            free(arr[i]);
    }
    free(arr);
}