#include "cub3d.h"

void    exit_check(enum exit_code code, s_file *file)
{
    switch (code)
    {
    case INVALID_NUMBER_ARGS:
        fprintf(stderr, "ERROR: Inavlid number of args\n");
        break;
    case MALLOC_ERR:
        fprintf(stderr, "ERROR: malloc\n");
        break;
    case FILE_DOENST_EXIST:
        fprintf(stderr, "ERROR: File doesn't exixt\n");
        break;
    case NO_READING_PERM:
        fprintf(stderr, "ERROR: Invalid file permissions\n");
        break;
    case NON_PRINTABLE_CHARS:
        fprintf(stderr, "ERROR: File name cnat have non-printable chars\n");
        break;
    case INVALID_TYPE_FILE:
        fprintf(stderr, "ERROR: File must terminate with .cub\n");
        break;
    case EMPTY_FILE:
        fprintf(stderr, "ERROR: File is empty\n");
        break;
    case INVALID_ID:
        fprintf(stderr, "ERROR: INVALID ID\n");
        break;
    case INVALID_NOTEXTURE_PATH:
        fprintf(stderr, "ERROR: INVALID NO texture\n");
        break;
    case INVALID_SOTEXTURE_PATH:
        fprintf(stderr, "ERROR: INVALID SO texture\n");
        break;
    case INVALID_EATEXTURE_PATH:
        fprintf(stderr, "ERROR: INVALID EA texture\n");
        break;
    case INVALID_WETEXTURE_PATH:
        fprintf(stderr, "ERROR: INVALID WE texture\n");
        break;
    case INVALID_COLOR_COORDINATES:
        fprintf(stderr, "ERROR: INVALID color coordinates\n");
        break;
    case EMPTY_LINE_INSIDE_MAP:
        fprintf(stderr, "ERROR: Empty line inside map\n");
        break;
    case INVALID_MAP_CHAR:
        fprintf(stderr, "ERROR: Invalid map char\n");
        break;
    case INVALID_WALLS:
        fprintf(stderr, "ERROR: Invalid walls\n");
        break;
    case INVALID_PLAYER_SPAWN:
        fprintf(stderr, "ERROR: Invalid spawn\n");
        break;
    default:
        break;
    }
    cleanup(file);
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
    exit(1);
}

void free_arr(char **arr, int index)
{
    int i;

    if (!arr)
        return;
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
}
