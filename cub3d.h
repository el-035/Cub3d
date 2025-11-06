#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
// # include "mlx_linux/mlx.h"
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
	char	**map_cpy;
	char	*n_texture;
	char	*s_texture;
	char	*e_texture;
	char	*w_texture;
	int f_color; // in hex
	int c_color; // in hex
	int		player_x;
	int		player_y;
	char	direction;
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
void	init(t_mlx *data, int nb_lines);
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
void	validate_map(t_mlx *data, char **map);
void	check_filename(t_mlx *data, char *file);
void	validate_input(int argc, char *argv[], t_mlx *data);
void	dup_map(t_mlx *data);
void	flood_fill(t_mlx *data);

// parsing
void    parsing(t_mlx *data, int argc, char *argv[]);
void parse_texture(t_mlx *data, t_input *input, char *line, int type);
void parse_color(t_mlx *data, t_input *input, char *line, int type);

// helpers
int     ft_isspace(int c);
int empty_line(char *line);
char *skip_whitespace(char *line);
void    print_map(char **map);
int     find_start(char *s);

// free & errors
void		parse_error(t_mlx *data, char *msg, int free_check);
void		free_exit(t_mlx *data, int errnum);
void		free_arr(char **arr);


// define errors

# define ERR_FILENAME "File must end with '.cub'" // 1
# define ERR_CUB "Something must preceed '.cub'" // 1
# define ERR_ARG_NB "Argument number invalid" // 1
# define ERR_NO_COL "Floor or ceiling color missing" // 1
# define ERR_INV_COL "Floor or ceiling color invalid" // 1
# define ERR_NO_TEX "Texture path missing" // 1
# define ERR_NO_SEP "No proper seperation between file contents" // 1
# define ERR_FILE_CONTENT "Invalid file content or layout" // 1
# define ERR_INV_TEX "Texture path invalid" // 1
# define ERR_PERM "Input file cannot be opened" // 1
# define ERR_NO_MAP "Input file has no map contents"

# define ERR_INV_MAP "Invalid map character" // 1
# define ERR_MAP_SPACE "Invalid spaces in map"
# define ERR_MAP_LINE "Empty line in map" // 1
# define ERR_START "Player surrounded by wall" // should this be invalid?
# define ERR_PLAYER "Map needs 1 player" // 1
# define ERR_NO_WALL "Map must be surrounded by walls" // 1

# define ERR_ALLOC "Allocation failure"
# define ERR_READ "Read error"

#endif
