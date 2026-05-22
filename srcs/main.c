/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:35:00 by htavares          #+#    #+#             */
/*   Updated: 2026/05/22 12:28:41 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_file	file;

	if (ac != 2)
		return (exit_check(invalid_number_args, NULL), 1);
	ft_memset(&file, 0, sizeof(file));
	file = parsing(&file, av);
	if (!exec(&file))
		return (1);
	return (0);
}
