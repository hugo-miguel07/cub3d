/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubfile_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 13:13:32 by antabord          #+#    #+#             */
/*   Updated: 2026/04/23 13:32:09 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

int    checking_cubfile(char *av)
{
    int fd;
    char buffer;
    int bytes_read;

    fd = -1;
    bytes_read = 0;
    if (!av)
        exit_check(FILE_DOENST_EXIST, NULL);
    if(!ft_strrchr(av, '.') || ft_strncmp(ft_strrchr(av, '.'), ".cub", 5) != 0)
        exit_check(INVALID_TYPE_FILE, NULL);
    fd = open(av, O_RDONLY);
    if (fd == -1)
        exit_check(NO_READING_PERM, NULL);
    bytes_read = read(fd, &buffer, 1);
    close(fd);
    if (!bytes_read)
        exit_check(EMPTY_FILE, NULL);
    if (bytes_read == -1)
        exit_check(NO_READING_PERM, NULL);
    fd = open(av, O_RDONLY);
    if (fd == -1)
        exit_check(NO_READING_PERM, NULL);
    return fd;
}
