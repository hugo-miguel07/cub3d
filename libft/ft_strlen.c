/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:53:02 by htavares          #+#    #+#             */
/*   Updated: 2026/04/21 11:57:27 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	if (!s)
		return 0;
	while (*s)
	{
		s++;
		size++;
	}
	return (size);
}
/*
#include <stdio.h>
int	main(void)
{
	char *c = "Quarenta";

	printf("%d", ft_strlen(c));
	return (0);
}
*/
