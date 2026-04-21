/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:35:00 by htavares          #+#    #+#             */
/*   Updated: 2026/04/21 17:01:07 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	s_file	gamefile;
	
	if (ac != 2)
		exit_check(INVALID_NUMBER_ARGS);
	gamefile = parsing(av);
	if (!exec(gamefile))
		return (cleanup_file(gamefile), 1);
	cleanup_file(gamefile);
	return (0);
}