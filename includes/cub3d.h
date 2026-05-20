/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:51:07 by htavares          #+#    #+#             */
/*   Updated: 2026/05/20 10:18:49 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef FOV
#  define FOV 100.00
# endif

# ifndef STEPSPEED
#  define STEPSPEED 0.04
# endif

# ifndef ROTATIONSPEED
#  define ROTATIONSPEED 0.02
# endif

# ifndef WINDOW_SIZE
#  define WIDTHW 1280
#  define HEIGHTW 720
# endif

/***************************Parsing******************************* */

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
	char	*NO_texture[2];
    char	*SO_texture[2];
	char	*WE_texture[2];
	char	*EA_texture[2];
	char	*F_color[2];
	char	*C_color[2];
	char	**map;
	int		player;
	int		fill_counter;
}	s_file;

void exit_check(enum exit_code code, s_file *file);  /*tem que aceitar os args daquilo que s tem que libertar*/
void free_arr(char **arr, int index);
void    cleanup(s_file *file);

s_file  parsing(s_file *file, char **av);
void	checking_file(int fd, s_file *file);
int     checking_cubfile(char *av);
void    filling_struct_part1(char *tmp, char *id, s_file *file);
void    filling_struct_part3(char *tmp, s_file *file);
void    checking_rgb(s_file *files);
void    checking_paths(s_file *file);
void    checking_chars_n_walls(s_file *file, char **map);
void    skip_spaces(char **ptr);
int     map_size(char **map);
void    map_cpy(s_file *file);
void    player_pos(s_file *file, char **cpy);
void    flood_fill(s_file *file, char **map, int y, int x);
void	exit_check(enum exit_code code, s_file *file);

/*--------------------Execution------------------------*/

typedef struct s_player
{
	double	px;
	double	py;
	double	angle;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}	t_player;

typedef struct s_input
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
}	t_input;

typedef struct s_frame
{
	void	*img_mlx;
	void	*pixels;
	int		width;
	int		height;
	int		bits_per_pix;
	int		line_length;
	int		endian;
}	t_frame;

typedef struct s_texture
{
	void	*img_mlx;
	void	*pixels;
	int		width;
	int		height;
	int		bits_per_pix;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_textures
{
	t_texture	no;
	t_texture	so;
	t_texture	we;
	t_texture	ea;
}	t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_frame		*frame;
	double		*zbuffer;
	t_textures	textures;
	t_player	player;
	t_input		input;
	s_file		*file;
}   t_game;


typedef struct s_rt_state
{
	// DDA stepping
	int				mapX;
	int				mapY;
	int				stepX;
	int				stepY;
	double			deltaDistX;
	double			deltaDistY;
	double			sideDistX;
	double			sideDistY;

	// Ray data
	double			rayDirX;
	double			rayDirY;
	double			cameraX;

	// Results
	int				side;
	int				hit;
	double			perpWallDist;

	// Wall rendering
	int				lineHeight;
	int				drawStart;
	int				drawEnd;
	unsigned int	color;
	t_texture		*tex;
}	t_rt_state;

typedef struct s_minimap
{
	int		height;
	int		width;
	int		tile_size;
	int		radius;
	int		x_offset;
	int		y_offset;
}	t_minimap;


int				exec(s_file *file);
void			cleanup_game(t_game *game);
void			find_player(t_game *game);
int				create_frame(t_game *game);
int				create_zbuffer(t_game *game);
int				load_textures(t_game *game);
void			destroy_textures(t_game *game);
void			game_loop(t_game *game);
void			draw_scene(t_game *game);
unsigned int	parse_rgb(char *str);
void			put_pixel(t_frame *f, int x, int y, unsigned int color);
void			init_ray(t_game *game, t_rt_state *rt, int x);
void			cast_dda(t_game *game, t_rt_state *rt);
void			calc_wall_height(t_game *game, t_rt_state *rt);
void			draw_minimap(t_game *game);
int				render(t_game *game);
int				move_player(t_game *game);
int				look_player(t_game *game);

#endif
