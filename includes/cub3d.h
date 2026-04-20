/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:51:07 by htavares          #+#    #+#             */
/*   Updated: 2026/04/20 17:44:35 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

/*--------------Parsing Declaration--------------------*/

enum exit_code {
    INVALID_NUMBER_ARGS,
    FILE_DOENST_EXIST,
    NO_READING_PERM,
    NON_PRINTABLE_CHARS,
    INVALID_TYPE_FILE,
    EMPTY_FILE,
    INVALID_ID,
};

typedef struct t_file{
    char **NO_texture;
    char **SO_texture;
    char **WE_texture;
    char **EA_texture;
    char **F_color;
    char **C_color;
    char **map;
}   s_file;

exit_check(enum exit_code code);

/*-------------Execution Declaration-------------------*/

# ifndef WIN_W
#  define WIN_W 1280
# endif

# ifndef WIN_H
#  define WIN_H 720
# endif

typedef struct	s_point
{
	int		x;
	int		y;
	char	orientation;
}	t_point;

typedef struct	s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		width;
	int		height;
	t_point	player;
	void	*img_wall;
	int		win_w;
	int		win_h;
}	t_game;

/*----------------Parsing Functions--------------------*/

s_file	*parsing(char **av);
int		checking_cubfile(char *av);

/*---------------Execution Functions-------------------*/

int		exec(s_file *gamefile);
t_point	find_player(char **map);

#endif
