/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:35:00 by htavares          #+#    #+#             */
/*   Updated: 2026/05/13 10:54:48 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	s_file file;
	
	if (ac != 2)
		exit_check(INVALID_NUMBER_ARGS, NULL);
	ft_memset(&file, 0, sizeof(file));
	file = parsing(&file, av);
	if (!exec(&file))
		return (1);
	return (0);
}
