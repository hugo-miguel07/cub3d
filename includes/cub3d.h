/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:51:07 by htavares          #+#    #+#             */
/*   Updated: 2026/04/23 17:53:29 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libft/libft.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

enum exit_code {
    MALLOC_ERR,
    INVALID_NUMBER_ARGS,
    FILE_DOENST_EXIST,
    NO_READING_PERM,
    NON_PRINTABLE_CHARS,
    INVALID_TYPE_FILE,
    EMPTY_FILE,
    INVALID_ID,
    INVALID_NOTEXTURE_PATH,
    INVALID_SOTEXTURE_PATH,
    INVALID_EATEXTURE_PATH,
    INVALID_WETEXTURE_PATH,
    INVALID_COLOR_COORDINATES,
    EMPTY_LINE_INSIDE_MAP,
    INVALID_MAP_CHAR,
    INVALID_WALLS,
    INVALID_PLAYER_SPAWN,
};


typedef struct t_file{
    char **NO_texture;
    char **SO_texture;
    char **WE_texture;
    char **EA_texture;
    char **F_color;
    char **C_color;
    char **map;
    int player;
    int fill_counter;
}   s_file;

exit_check(enum exit_code code, s_file *file);  /*tem que aceitar os args daquilo que s tem que libertar*/
void free_arr(char **arr);

/*---------------------Parsing-------------------------*/

s_file    parsing(s_file *file, char **av);
int     checking_cubfile(char *av);
void    filling_struct_part1(char *tmp, char *id, s_file *file);
void    checking_rgb(s_file *files);
void    checking_paths(s_file *file);
void    checking_chars_n_walls(s_file *file, char **map);
void    skip_spaces(char **ptr);
int  map_size(char **map);