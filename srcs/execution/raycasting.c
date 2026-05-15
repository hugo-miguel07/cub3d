/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:32:42 by htavares          #+#    #+#             */
/*   Updated: 2026/05/15 15:05:35 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_game *game, t_rt_state *rt, int x)
{
    rt->cameraX = 2.0 * x / (double)game->frame->width - 1.0;
    rt->rayDirX = game->player.dirX + game->player.planeX * rt->cameraX;
    rt->rayDirY = game->player.dirY + game->player.planeY * rt->cameraX;
}

void	cast_dda(t_game *game, t_rt_state *rt)
{
    double px = game->player.px;
    double py = game->player.py;

    rt->mapX = (int)px;
    rt->mapY = (int)py;
    rt->deltaDistX = (rt->rayDirX == 0.0) ? 1e30 : fabs(1.0 / rt->rayDirX);
    rt->deltaDistY = (rt->rayDirY == 0.0) ? 1e30 : fabs(1.0 / rt->rayDirY);
    if (rt->rayDirX < 0)
    {
        rt->stepX = -1;
        rt->sideDistX = (px - rt->mapX) * rt->deltaDistX;
    }
    else
    {
        rt->stepX = 1;
        rt->sideDistX = (rt->mapX + 1.0 - px) * rt->deltaDistX;
    }
    if (rt->rayDirY < 0)
    {
        rt->stepY = -1;
        rt->sideDistY = (py - rt->mapY) * rt->deltaDistY;
    }
    else
    {
        rt->stepY = 1;
        rt->sideDistY = (rt->mapY + 1.0 - py) * rt->deltaDistY;
    }
    rt->hit = 0;
    rt->side = 0;
    while (!rt->hit)
    {
        if (rt->sideDistX < rt->sideDistY)
        {
            rt->sideDistX += rt->deltaDistX;
            rt->mapX += rt->stepX;
            rt->side = 0;
        }
        else
        {
            rt->sideDistY += rt->deltaDistY;
            rt->mapY += rt->stepY;
            rt->side = 1;
        }
        if (!game->file->map[rt->mapX] || rt->mapY < 0 || !game->file->map[rt->mapX][rt->mapY])
        {
            rt->hit = 1;
            break;
        }
        if (game->file->map[rt->mapX][rt->mapY] == '1')
            rt->hit = 1;
    }
    if (rt->side == 0)
        rt->perpWallDist = rt->sideDistX - rt->deltaDistX;
    else
        rt->perpWallDist = rt->sideDistY - rt->deltaDistY;
    if (rt->perpWallDist <= 0.0)
        rt->perpWallDist = 1e30;
}

void	calc_wall_height(t_game *game, t_rt_state *rt)
{
    rt->lineHeight = (int)(game->frame->height / rt->perpWallDist);
    rt->drawStart = -rt->lineHeight / 2 + game->frame->height / 2;
    if (rt->drawStart < 0)
        rt->drawStart = 0;
    rt->drawEnd = rt->lineHeight / 2 + game->frame->height / 2;
    if (rt->drawEnd >= game->frame->height)
        rt->drawEnd = game->frame->height - 1;
    rt->color = 0x00FFFFFF;
    if (rt->side == 1)
        rt->color = (rt->color >> 1) & 8355711;
}
