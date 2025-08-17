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
# include "libft/libft.h"

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
    int line_length;
    int line_count;
}           t_input;

typedef struct s_mlx
{
    t_input *input;
	void	*mlx;
	void	*window;
}			t_mlx;


//destroy and errors
int	destroy_everything(t_mlx *data);

#endif