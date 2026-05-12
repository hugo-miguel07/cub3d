/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zbuffer_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 13:18:06 by htavares          #+#    #+#             */
/*   Updated: 2026/05/12 15:00:34 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_zbuffer(t_game *game)
{
	if (!game)
		return (0);
	game->zbuffer = ft_calloc(WIDTHW, sizeof(double));
	if (!game->zbuffer)
		return (0);
	return (1);
}
