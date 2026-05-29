/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antabord <antabord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:51:07 by htavares          #+#    #+#             */
/*   Updated: 2026/05/22 12:55:39 by antabord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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

enum				e_exit_code
{
	malloc_err,
	invalid_number_args,
	file_doesnt_exist,
	invalid_file,
	non_printable_chars,
	invalid_type_file,
	empty_file,
	invalid_id,
	invalid_notexture_path,
	invalid_sotexture_path,
	invalid_eatexture_path,
	invalid_wetexture_path,
	inavlid_colo_coordinates,
	empty_line_inside_map,
	invalid_map_char,
	invalid_walls,
	invalid_spawn,
	invalid_map_size,
};

typedef struct s_file
{
	char			*no_texture[2];
	char			*so_texture[2];
	char			*we_texture[2];
	char			*ea_texture[2];
	char			*f_color[2];
	char			*c_color[2];
	char			**map;
	int				player;
	int				fill_counter;
}					t_file;

void				exit_check(enum e_exit_code code, t_file *file);
/*tem que aceitar os args daquilo que s tem que libertar*/
int					free_arr(char **arr, int index);
void				cleanup(t_file *file);

t_file				parsing(t_file *file, char **av);
int					checking_file(int fd, t_file *file);
int					checking_cubfile(char *av);
void				filling_struct_part1(char *tmp, char *id, t_file *file);
void				filling_struct_part3(char *tmp, t_file *file);
int					checking_rgb(t_file *files);
int					checking_paths(t_file *file);
int					checking_chars_n_walls(t_file *file, char **map);
void				skip_spaces(char **ptr);
int					map_size(char **map);
int					map_cpy(t_file *file);
int					player_pos(t_file *file, char **cpy);
int					flood_fill(t_file *file, char **map, int y, int x);
void				exit_check(enum e_exit_code code, t_file *file);
int					texture_validation(t_file *file);

/*--------------------Execution------------------------*/

typedef struct s_player
{
	double			px;
	double			py;
	double			angle;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
}					t_player;

typedef struct s_input
{
	int				w;
	int				s;
	int				a;
	int				d;
	int				left;
	int				right;
}					t_input;

typedef struct s_frame
{
	void			*img_mlx;
	void			*pixels;
	int				width;
	int				height;
	int				bits_per_pix;
	int				line_length;
	int				endian;
}					t_frame;

typedef struct s_texture
{
	void			*img_mlx;
	void			*pixels;
	int				width;
	int				height;
	int				bits_per_pix;
	int				line_length;
	int				endian;
}					t_texture;

typedef struct s_textures
{
	t_texture		no;
	t_texture		so;
	t_texture		we;
	t_texture		ea;
}					t_textures;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_frame			*frame;
	double			*zbuffer;
	t_textures		textures;
	t_player		player;
	t_input			input;
	t_file			*file;
}					t_game;

typedef struct s_rt_state
{
	// DDA stepping
	int				mapx;
	int				mapy;
	int				stepx;
	int				stepy;
	double			deltadistx;
	double			deltadisty;
	double			sidedistx;
	double			sidedisty;

	// Ray data
	double			raydirx;
	double			raydiry;
	double			camerax;

	// Results
	int				side;
	int				hit;
	double			perpwalldist;

	// Wall rendering
	int				lineheight;
	int				drawstart;
	int				drawend;
	unsigned int	color;
	t_texture		*tex;
}					t_rt_state;

typedef struct s_minimap
{
	int				height;
	int				width;
	int				tile_size;
	int				radius;
	int				x_offset;
	int				y_offset;
	unsigned int	color;
}					t_minimap;

int					exec(t_file *file);
void				cleanup_game(t_game *game);
void				find_player(t_game *game);
int					create_frame(t_game *game);
int					create_zbuffer(t_game *game);
int					load_textures(t_game *game);
void				destroy_textures(t_game *game);
void				game_loop(t_game *game);
void				draw_scene(t_game *game);
unsigned int		parse_rgb(char *str);
void				put_pixel(t_frame *f, int x, int y, unsigned int color);
void				init_ray(t_game *game, t_rt_state *rt, int x);
void				cast_dda(t_game *game, t_rt_state *rt);
void				calc_wall_height(t_game *game, t_rt_state *rt);
void				draw_minimap(t_game *game);
int					render(t_game *game);
int					move_player(t_game *game);
int					look_player(t_game *game);
void				init_dda_params(t_game *game, t_rt_state *rt, double *px,
						double *py);
void				init_steps(t_rt_state *rt, double px, double py);
int					is_outside_map(t_game *game, t_rt_state *rt);
void				draw_map(t_game *game);
unsigned int		get_texel(t_texture *tex, int x, int y);

#endif
