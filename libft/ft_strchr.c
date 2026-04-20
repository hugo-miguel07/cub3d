/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:11:59 by htavares          #+#    #+#             */
/*   Updated: 2026/04/20 13:42:20 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	letra;

	letra = (char)c;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == letra)
			return ((char *)&s[i]);
		i++;
	}
	if (!s[i] && s[i] == letra)
		return ((char *)&s[i]);
	return ((void *)0);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*s = "Patapim";
	int	c = 't' + 256;
	printf("%s\n", s);
	s = ft_strchr(s, c);
	printf("%s\n", s);
	printf("%s", strchr(s, c));
}
*/
