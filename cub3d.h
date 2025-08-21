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
	char	**map;
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
	char 	**file;
	int		info_count;
}			t_input;

typedef struct s_mlx
{
	t_input	*input;
	void	*mlx;
	void	*window;
}			t_mlx;

// destroy and errors
int			destroy_everything(t_mlx *data);

// PARSING
// init
void	init(t_mlx *data, int filelines);
void    process_line(t_mlx *data, t_input *input, char *line, int type);
void	fill_struct(t_mlx *data);

// parse
void    check_line(t_mlx *data, char *line);
void    process_file(t_mlx *data, t_input *input);
int    read_file(char *path, t_mlx *data, int process);


// map
void check_map_dimensions(t_mlx *data, t_input *input, char **arr);
void    fill_map(t_input *input, char **arr);
void    alloc_map(t_mlx *data);


// validation
void	validate_map(char *argv[]);
void	check_filename(t_mlx *data, char *file);
void	validate_input(int argc, char *argv[], t_mlx *data);

// helpers
int     ft_isspace(int c);
char *skip_whitespace(char *line);
void    print_map(char **map);

// free & errors
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
# define ERR_EXTRA_CHAR	"Invalid char(s) after texture filename or F/C color"
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
# define ERR_FILE_CONTENT "Invalid file content or layout"

# define ERR_ALLOC "Allocation failure"
# define ERR_READ "Read error"

#endif