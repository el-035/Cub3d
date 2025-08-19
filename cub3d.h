#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "mlx_linux/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>


typedef struct s_input
{
	char	**input_map;
	char	*n_texture;
	char	*s_texture;
	char	*e_texture;
	char	*w_texture;
	int f_color; // in hex
	int c_color; // in hex
	int		player_x;
	int		player_y;
	char	direction[2];
	int		line_length;
	int		line_count;
}			t_input;

typedef struct s_mlx
{
	t_input	*input;
	void	*mlx;
	void	*window;
}			t_mlx;

// destroy and errors
int			destroy_everything(t_mlx *data);
void		parse_error(t_mlx *data, char *msg);
void		free_exit(t_mlx *data, int errnum);
void		free_arr(char **arr);

// define errors
# define ERR_FILENAME "File must end with '.cub'" // 1
# define ERR_CUB "Something must preceed '.cub'" // 1
# define ERR_ARG_NB "Argument number invalid" // 1
# define ERR_FILE "Input file does not exist"
# define ERR_PERM "Input file cannot be opened"
# define ERR_NO_MAP "Input file has no map contents"
# define ERR_INFO "Input file misses texture information"
# define ERR_NO_COL "Floor or ceiling color missing"
# define ERR_INV_COL "Floor or ceiling color invalid"
# define ERR_NO_TEX "Texture path missing"
# define ERR_INV_TEX "Texture path invalid"
# define ERR_MAP_LOCATION "Map content must be last"

# define ERR_INV_MAP "Invalid map character"
# define ERR_MAP_SPACE "Invalid spaces in map"
# define ERR_MAP_LINE "Empty line in map"
# define ERR_START "Player surrounded by wall"
# define ERR_NO_WALL "Map must be surrounded by walls"
# define ERR_FILE_CONTENT "Invalid file content (only texture information, \
floor/ceiling color and map is allowed)"

# define ERR_ALLOC "Allocation failure"
# define ERR_READ "Read error"

#endif