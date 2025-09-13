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
#define FOV 66	//change		//NOT USED SO FAR
//#define PLANE 0,66	//change	//NOT USED SO FAR
#define M_PI 3.14159265358979323846
#define HALF_FOV 0.57596
#define ROTATION 0.03
#define MOVEMENT 0.07

//#define V_WALL 0;
//#define H_WALL 1;

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


//delete
#define GRAY 0x808080
#define T_WINDOW_WIDTH 1300 //1280
#define T_WINDOW_HEIGHT 800 //720
#define T_TILE_SIZE 100// 90	//change


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
    char **input_map;
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

	double dist_y;
	double dist_x;

	double side_dist_y;
	double side_dist_x;

	int y;
	int x;

	double	pixel_pos;	//those could be merged into one
	int		pixel;		//and directly calculate texture x

	int wall;

	double distance;
	double corr_dis;

	int		wall_height;
	int		wall_start;
	int		wall_end;
	int		img_start;
	//int		img_end;
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
	//char **map;

}			t_game;

typedef struct s_mlx
{
    t_input *input;
	t_game	*game;
	void	*mlx;
	void	*window;
	t_texture *screen_data;


	void 	*test_window;
	void	*test_tile;
	void	*test_back;

}			t_mlx;


//main
void save_screen_buffer(t_mlx *data, t_ray *ray);


//calculations
int test_start(t_mlx *mlx);
int calculate_rays(t_mlx *mlx);	//probably to be deleted
double calculate_dir(t_game *game, t_input *input, double dir_x, double dir_y);


//movements
int events(int key, t_mlx *mlx);

//destroy and errors
int	destroy_everything(t_mlx *data);


//testing to be deleted afterwards
t_input *create_hardcoded_map(void);
void draw_2d_map_simple(t_mlx *mlx);
void	draw_ray(t_mlx *mlx, t_ray *ray, int color, double dir_x, double dir_y);
void	draw_grid(t_mlx *mlx, int win_width, int win_height);
void draw_back(t_mlx *mlx);

#endif