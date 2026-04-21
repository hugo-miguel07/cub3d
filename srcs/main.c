/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:35:00 by htavares          #+#    #+#             */
/*   Updated: 2026/04/21 15:25:42 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	s_file file;
	
	if (ac != 2)
		exit_check(INVALID_NUMBER_ARGS, NULL);
	ft_memset(&file, 0, sizeof(file));
	file = parsing(&file, av);
	av = NULL;
	return (0);
}