#include "cub3d.h"

exit_check(enum exit_code code, s_file *file)
{
    switch (code)
    {
    case INVALID_NUMBER_ARGS:
        
        break;
    
    default:
        break;
    }
    cleanup_exit
}

void free_arr(char **arr)
{
    int i;

    i = -1;
    while (arr[++i])
        free(arr[i]);
    free(arr);
}