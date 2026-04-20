/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:35:00 by htavares          #+#    #+#             */
/*   Updated: 2026/04/20 11:31:40 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	if (ac != 2)
		exit_check(INVALID_NUMBER_ARGS);
	parsing(av);
	av = NULL;
	return (0);
}