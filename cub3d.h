#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include "mlx_linux/mlx.h"
# include <sys/time.h>
# include <unistd.h>
# include <mlx.h>
# include <math.h>
# include "libft/libft.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define TILE_SIZE 128	//to be removed, use froom addr data
#define M_PI 3.14159265358979323846
#define HALF_FOV 0.57596
#define ROTATION 0.03
#define MOVEMENT 0.07

#define N 0
#define S 1
#define W 2
#define E 3

//KEYS
#define ESC 65307  
#define ROT_LEFT 65361  
#define ROT_RIGHT 65363 
#define UP 119       
#define LEFT 97        
#define DOWN 115       
#define RIGHT 100       


typedef struct s_texture
{
	char 	*file_name; //idk if needed
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}		t_texture;


typedef struct s_input
{
    char **map;
    t_texture *n_texture;
    t_texture *s_texture;
    t_texture *w_texture;
    t_texture *e_texture;
    int f_color; // in hex
    int c_color; // in hex
    int player_x;
    int player_y;
	char direction;
    int line_length;
    int line_count;
}           t_input;

typedef struct s_ray
{
	double ray_dir_x;
	double ray_dir_y;

	int	step_x;
	int step_y;

	double delta_dist_x;
	double delta_dist_y;

	double side_dist_y;
	double side_dist_x;

	int y;
	int x;

	double	x_pos;

	int wall;

	double distance;

	int		wall_height;
	int		wall_start;
	int		wall_end;
	int		img_start;
	double		camera;
}			t_ray;

typedef struct s_game
{
	double pos_x;
	double pos_y;

	double dir_x;
	double dir_y;

	double plane_x;
	double plane_y;

	double angle;

	t_ray *ray;
}			t_game;

typedef struct s_mlx
{
    t_input *input;
	t_game	*game;
	void	*mlx;
	void	*window;
	t_texture *screen_data;
}			t_mlx;


//main

//visuals
void	put_wall(t_mlx *data, int y, int x, t_texture *wall);
void save_screen_buffer(t_mlx *data, t_ray *ray);


//init stuff
t_input *init_stuff(t_mlx *data);
int save_img(t_mlx *data);
int init_game(t_mlx *mlx);

//calculations
void dist_calc(t_game *game);
void init_step_pos(t_game *game);
void calculate_dir(t_game *game, t_input *input);
t_texture *find_dir(t_mlx *data, t_game *game, t_ray *ray, int x);

//calculations utils
int	side_dist_x(t_game *game, t_input *input);
int	side_dist_y(t_game *game, t_input *input);
t_texture	*wall_side(t_mlx *data, t_ray *ray);
void	wall_height(t_ray *ray, t_texture *img);

//movements
int events(int key, t_mlx *mlx);

//destroy and errors
int	destroy_everything(t_mlx *data);


//testing to be deleted afterwards
t_input *create_hardcoded_map(void);
/* void draw_2d_map_simple(t_mlx *mlx);
void	draw_ray(t_mlx *mlx, t_ray *ray, int color, double dir_x, double dir_y);
void	draw_grid(t_mlx *mlx, int win_width, int win_height);
void draw_back(t_mlx *mlx); */

#endif