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
#define TILE_SIZE 90	//change
#define FOV 66	//change
#define PLANE 0,66	//change

//THESE TO BE DELETED
#define COLOR_WALL     0xFFFFFF
#define COLOR_FLOOR    0x000000
#define COLOR_PLAYER   0xFF0000
#define COLOR_RAY      0x00FF00


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

typedef struct s_game
{
	double pos_x;
	double pos_y;

	double dir_x;
	double dir_y;

	double plane_x;
	double plane_y;

	//char **map;

}			t_game;

typedef struct s_mlx
{
    t_input *input;
	t_game	*game;
	void	*mlx;
	void	*window;
}			t_mlx;




//destroy and errors
int	destroy_everything(t_mlx *data);


//testing to be deleted afterwards
t_input *create_hardcoded_map(void);

#endif