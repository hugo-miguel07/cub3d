#include "cub3d.h"

static void	set_to_default(t_minimap *mm)
{
    mm->height = 0;
    mm->width = 0;
    mm->radius = 5;
    mm->x_offset = 10;
    mm->y_offset = 10;
    mm->tile_size = 8;
}

static void putting_map_pixel(t_game *game, t_minimap *mm)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < mm->tile_size)
    {
        x = 0;
            while (x < mm->tile_size)
            {
                put_pixel(game->frame,
                    mm->x_offset + map_x * mm->tile_size + x,
                    mm->y_offset + map_y * mm->tile_size + y,
                    color);
                x++;
            }
            y++;
    }
}

static void	draw_map(t_game *game, t_minimap *mm)
{
    int				map_y;
    int				map_x;
    int				x;
    int				y;
    unsigned int	color;

    map_y = 0;
    while (game->file->map[map_y++])
    {
        map_x = 0;
        while (game->file->map[map_y][map_x++])
        {
            if (game->file->map[map_y][map_x] == '1')
                color = 0x00FFFFFF;
            else if (game->file->map[map_y][map_x] == '0'
                || game->file->map[map_y][map_x] == 'N'
                || game->file->map[map_y][map_x] == 'S'
                || game->file->map[map_y][map_x] == 'E'
                || game->file->map[map_y][map_x] == 'W')
                color = 0x00333333;
            else
                color = 0x00000000;
        }
    }
}

static void	draw_player(t_game *game, t_minimap *mm)
{
    int	px;
    int	py;
    int	x;
    int	y;

    px = mm->x_offset + (int)game->player.px * mm->tile_size;
    py = mm->y_offset + (int)game->player.py * mm->tile_size;
    y = -2;
    while (y <= 2)
    {
        x = -2;
        while (x <= 2)
        {
            put_pixel(game->frame, px + x, py + y, 0x00FF0000);
            x++;
        }
        y++;
    }
}

void	draw_minimap(t_game *game)
{
    t_minimap	mini_map;

    if (!game || !game->frame || !game->file || !game->file->map)
        return ;
    set_to_default(&mini_map);
    draw_map(game, &mini_map);
    draw_player(game, &mini_map);
}



void    draw_minimap(t_game *game)
{
    t_minimap   mini_map;

    if (!game || !game->frame || !game->file || !game->file->map)
        return ;
    set_to_default(&mini_map);
    draw_map(&mini_map, game);
    draw_player(&mini_map, game);
}

