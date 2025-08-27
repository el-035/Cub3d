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

#define WINDOW_WIDTH 1000//1280
#define WINDOW_HEIGHT 600//720
#define TILE_SIZE 100// 90	//change
#define FOV 66	//change
#define PLANE 0,66	//change

//KEYS
#define ESC 65307
#define UP 65362
#define DOWN 65364  
#define LEFT 65361  
#define RIGHT 65363 
#define W 119       
#define A 97        
#define S 115       
#define D 100       


//delete
#define GRAY 0x808080


typedef struct s_input
{
    char **input_map;
    char *n_texture;
    char *s_texture;
    char *w_texture;
    char *e_texture;
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

	double distance;
}			t_ray;

typedef struct s_game
{
	double pos_x;
	double pos_y;

	double dir_x;
	double dir_y;

	double plane_x;
	double plane_y;

	t_ray *ray;
	//char **map;

}			t_game;

typedef struct s_mlx
{
    t_input *input;
	t_game	*game;
	void	*mlx;
	void	*window;
	void 	*test_window;
	void	*test_tile;
	void	*test_back;

}			t_mlx;




//destroy and errors
int	destroy_everything(t_mlx *data);


//testing to be deleted afterwards
t_input *create_hardcoded_map(void);
void draw_2d_map_simple(t_mlx *mlx);
void	draw_ray(t_mlx *mlx, t_ray *ray, int color, double dir_x, double dir_y);
void	draw_grid(t_mlx *mlx, int win_width, int win_height);
void draw_back(t_mlx *mlx);
#endif