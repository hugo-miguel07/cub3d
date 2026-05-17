#include "cub3d.h"
static t_minimap set_default(t_minimap mm)
{
    
}

void    draw_minimap(t_game *game)
{
    t_minimap   mini_map;

    if (!game || !game->frame || !game->file || !game->file->map)
        return ;
    ft_memset(&mini_map, 0, sizeof(t_minimap));
}

