/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 17:09:41 by htavares          #+#    #+#             */
/*   Updated: 2026/05/22 12:43:25 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_texel(t_texture *tex, int x, int y)
{
	char	*dst;
	int		offset;

	if (!tex || !tex->pixels)
		return (0);
	if (x < 0 || y < 0 || x >= tex->width || y >= tex->height)
		return (0);
	offset = (y * tex->line_length) + (x * (tex->bits_per_pix / 8));
	dst = (char *)tex->pixels + offset;
	return (*(unsigned int *)dst);
}

void	put_pixel(t_frame *f, int x, int y, unsigned int color)
{
	char	*dst;
	int		offset;

	if (!f || !f->pixels || x < 0 || y < 0 || x >= f->width || y >= f->height)
		return ;
	offset = (y * f->line_length) + (x * (f->bits_per_pix / 8));
	dst = (char *)f->pixels + offset;
	*(unsigned int *)dst = color;
}

static int	read_component(char **s)
{
	int	n;

	while (**s == ' ' || **s == '\t')
		(*s)++;
	n = ft_atoi(*s);
	while (ft_isdigit(**s))
		(*s)++;
	while (**s == ' ' || **s == '\t')
		(*s)++;
	if (**s == ',')
		(*s)++;
	return (n);
}

unsigned int	parse_rgb(char *str)
{
	char	*p;
	int		r;
	int		g;
	int		b;

	if (!str)
		return (0);
	p = str;
	r = read_component(&p);
	g = read_component(&p);
	b = read_component(&p);
	return ((r << 16) | (g << 8) | b);
}
