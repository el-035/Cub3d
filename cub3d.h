/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:48:54 by efittant          #+#    #+#             */
/*   Updated: 2025/11/19 17:59:19 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

# define TILE_SIZE 15
# define GRAY 0x808080
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define BLUE 0x0000FF
# define RED 0xFF0000

# define M_PI 3.14159265358979323846
# define HALF_FOV 0.57596
# define ROTATION 0.01
# define MOVEMENT 0.025

# define N 0
# define S 1
# define W 2
# define E 3

// KEYS
# define ESC 65307
# define ROT_LEFT 65361
# define ROT_RIGHT 65363
# define UP 119
# define LEFT 97
# define DOWN 115
# define RIGHT 100
# define M 109
# define Q 113

enum e_key
{
	K_ROT_LEFT,
	K_ROT_RIGHT,
	K_UP,
	K_LEFT,
	K_DOWN,
	K_RIGHT,
};

typedef struct s_texture
{
	char		*file_name;
	void		*img;
	char		*data;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_texture;

typedef struct s_input
{
	char		**map;
	char		**map_cpy;
	t_texture	*n_texture;
	t_texture	*s_texture;
	t_texture	*w_texture;
	t_texture	*e_texture;
	int			f_color;
	int			c_color;
	int			player_x;
	int			player_y;
	char		direction;
	int			line_length;
	int			line_count;
	char		**file;
	int			info_count;
}				t_input;

typedef struct s_ray
{
	double		ray_dir_x;
	double		ray_dir_y;
	int			step_x;
	int			step_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_y;
	double		side_dist_x;
	int			y;
	int			x;
	double		x_pos;
	int			wall;
	double		distance;
	int			wall_height;
	int			wall_start;
	int			wall_end;
	int			img_start;
	double		camera;
}				t_ray;

typedef struct s_game
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		angle;
	t_ray		*ray;
}				t_game;

typedef struct s_mlx
{
	t_input		*input;
	t_game		*game;
	void		*mlx;
	void		*window;
	t_texture	*screen_data;
	t_texture	*mini_map;
	void		*window_map;
	int			is_map;
	int			kill_map;
	int			keys[6];
}				t_mlx;

// main
int				save_img(t_mlx *data, t_input *input);

// visuals
void			put_wall(t_mlx *data, int y, int x, t_texture *wall);
void			save_screen_buffer(t_mlx *data, t_ray *ray);

// init stuff
void			init_stuff(t_mlx *data);
void			init_game(t_mlx *mlx);
int				save_img_ew(t_mlx *data, t_texture *e_texture,
					t_texture *w_texture);
int				save_screen(t_mlx *data, t_texture *screen_data, t_texture *map);
int				save_img_ns(t_mlx *data, t_texture *n_texture,
					t_texture *s_texture);

// calculations
void			dist_calc(t_game *game);
void			init_step_pos(t_game *game);
void			calculate_dir(t_game *game, t_input *input);
t_texture		*find_dir(t_mlx *data, t_game *game, t_ray *ray, int x);

// calculations utils
int				side_dist_x(t_game *game, t_input *input);
int				side_dist_y(t_game *game, t_input *input);
t_texture		*wall_side(t_mlx *data, t_ray *ray);
void			wall_height(t_ray *ray, t_texture *img);

//keys
int	key_press(int key, t_mlx *data);
int	key_release(int key, t_mlx *data);
int				events(t_mlx *mlx);

// movements
int	is_wall(t_mlx *mlx, double x, double y);
int	up_down(int key, t_mlx *mlx);
int	left_right(int key, t_mlx *mlx);
int	rotate(int key, t_mlx *mlx);

//map
void init_map(t_mlx *data, t_input *input);

// destroy and errors
int				destroy_everything(t_mlx *data);
int				kill_map(t_mlx * data);
// PARSING
// init
void			init(t_mlx *data, int nb_lines);
void			process_line(t_mlx *data, t_input *input, char *line, int type);
void			fill_struct(t_mlx *data);

// parse
void			check_line(t_mlx *data, char *line);
void			process_file(t_mlx *data, t_input *input);
int				read_file(char *path, t_mlx *data, int process);

// map
void			check_map_dimensions(t_mlx *data, t_input *input, char **arr);
void			fill_map(t_input *input, char **arr);
void			alloc_map(t_mlx *data);

// validation
void			check_chars(t_mlx *data, char **map);
void			check_filename(t_mlx *data, char *file);
void			dup_map(t_mlx *data);
void			flood_fill(t_mlx *data);

// parsing
void			parsing(t_mlx *data, int argc, char *argv[]);
void			parse_texture(t_mlx *data, t_input *input, char *line,
					int type);
void			parse_color(t_mlx *data, t_input *input, char *line, int type);

// helpers
int				is_validchar(char c);
int				is_direction(char c);
int				ft_isspace(int c);
int				empty_line(char *line);
char			*skip_whitespace(char *line);
void			print_map(char **map);
int				find_start(char *s);
int				add_line(t_mlx *data, char *next_line, int fd, int i);
void			check_overflow(t_mlx *data, char **rgb);
void			map_empty_line(t_mlx *data, char **map, int a);

// free & errors
void			parse_error(t_mlx *data, char *msg, int free_check);
void			free_exit(t_mlx *data, int errnum);
void			free_arr(char **arr);

// define errors

# define ERR_FILENAME "File must end with '.cub'"
# define ERR_CUB "Something must preceed '.cub'"
# define ERR_ARG_NB "Argument number invalid"
# define ERR_NO_COL "Floor or ceiling color missing"
# define ERR_INV_COL "Floor or ceiling color invalid"
# define ERR_NO_TEX "Texture path missing"
# define ERR_NO_SEP "No proper seperation between file contents"
# define ERR_FILE_CONTENT "Invalid file content or layout"
# define ERR_INV_TEX "Texture path invalid"
# define ERR_PERM "Input file cannot be opened"
# define ERR_NO_MAP "Input file has no map contents"
# define ERR_DOUBLE_TEX "Direction texture mentioned twice"
# define ERR_DOUBLE_COL "Floor or Ceiling color mentioned twice"
# define ERR_INV_MAP "Invalid map character"
# define ERR_MAP_SPACE "Invalid spaces in map"
# define ERR_MAP_LINE "Empty line in map"
# define ERR_START "Player surrounded by wall"
# define ERR_PLAYER "Map needs 1 player"
# define ERR_NO_WALL "Map must be surrounded by walls"
# define ERR_OVERFLOW "Integer overflow"

# define ERR_ALLOC "Allocation failure"
# define ERR_READ "Read error"

# define ERR_ARG "Invalid argument"
# define MLX_FAIL "MLX failed"

#endif
