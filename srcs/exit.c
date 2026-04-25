#include "cub3d.h"

exit_check(enum exit_code code, s_file *file)
{
    switch (code)
    {
    case INVALID_NUMBER_ARGS:
        perror("ERROR: Inavlid number of args");
        break;
    case MALLOC_ERR:
        perror("ERROR: malloc");
        break;
    case FILE_DOENST_EXIST:
        perror("ERROR: File doesn't exixt");
        break;
    case NO_READING_PERM:
        perror("ERROR: Invalid file permissions");
        break;
    case NON_PRINTABLE_CHARS:
        perror("ERROR: File name cnat have non-printable chars");
        break;
    case INVALID_TYPE_FILE:
        perror("ERROR: File must terminate with ".cub"");
        break;
    case EMPTY_FILE:
        perror("ERROR: File is empty");
    case INVALID_ID:
        perror("ERROR: INVALID ID");
        break;
    case INVALID_NOTEXTURE_PATH:
        perror("ERROR: INVALID NO texture");
        break,
    case INVALID_SOTEXTURE_PATH:
        perror("ERROR: INVALID SO texture");
        break;
    case INVALID_EATEXTURE_PATH:
        perror("ERROR: INVALID EA texture");
        break;
    case INVALID_WETEXTURE_PATH:
        perror("ERROR: INVALID WE texture");
    case INVALID_COLOR_COORDINATES:
        perror("ERROR: INVALID color coordinates");
        break;
    case EMPTY_LINE_INSIDE_MAP:
        perror("ERROR: Empty line inside map");
        break;
    case EMPTY_LINE_INSIDE_MAP:
        perror("ERROR: Empty line inside map");
        break;
    case INVALID_MAP_CHAR:
        perror("ERROR: Invalid map char");
        break;
    case INVALID_WALLS:
        perror("ERROR: Invalid walls");
        break;
    case INVALID_PLAYER_SPAWN:
        perror("ERROR: Invalid spawn");
        break;
    default:
        break;
    }
    cleanup_exit
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