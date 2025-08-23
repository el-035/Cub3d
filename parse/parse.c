#include "../cub3d.h"

// open, close, read, write,
// printf, malloc, free, perror,
// strerror, exit, gettimeofday

// NO, SO, WE, EA and path
// F/C and valid color (range 0-255)
// multiple lines between input type OK
// no empty lines in map content
// map has to be last
// check textures exist and have permissions

int	_line(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && ft_isspace(s[i]))
		i++;
	if (s && s[i] && s[i] != '\n')
		return (0);
	return (1);
}

int	add_line(t_mlx *data, char *next_line, int fd, int i)
{
	data->input->file[i] = ft_strdup(next_line);
	if (!data->input->file[i])
		(free(next_line), close(fd), parse_error(data, ERR_ALLOC));
	return (1);
}

void	read_file(char *path, t_mlx *data, int process)
{
	int		fd;
	int		i;
	char	*next_line;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		parse_error(data, ERR_PERM);
	while (1)
	{
		next_line = get_next_line(fd); // add flag
		if (!next_line)
			break ;
		data->input->line_count++;
		if (process)
			i += add_line(data, next_line, fd, i);
		free(next_line);
	}
	close(fd);
}

int	process_pre_map(t_mlx *data, t_input *input, int i)
{
	int	type;

	type = 0;
	if (input->info_count < 6)
		input->file[i] = skip_whitespace(input->file[i]);
	if (!ft_strncmp("NO", input->file[i], 2)) // change to == 0
		type = 1;
	else if (!ft_strncmp("SO", input->file[i], 2))
		type = 2;
	else if (!ft_strncmp("EA", input->file[i], 2))
		type = 3;
	else if (!ft_strncmp("WE", input->file[i], 2))
		type = 4;
	if (type > 0 && type <= 4)
		parse_texture(data, input, input->file[i], type);
	if (!ft_strncmp("F", input->file[i], 1))
		type = 5;
	else if (!ft_strncmp("C", input->file[i], 1))
		type = 6;
	if (type == 5 || type == 6)
		parse_color(data, input, input->file[i], type);
	if (type > 0)
		input->info_count++;
	return (type);
}

void	process_file(t_mlx *data, t_input *input)
{
	int	i;

	i = 0;
	while (input->file && input->file[i] && (input->info_count < 6 || empty_line(input->file[i])))
	{
		if (!empty_line(input->file[i]) && process_pre_map(data, input, i) == 0)
			parse_error(data, ERR_FILE_CONTENT);
		i++;
	}
	check_map_dimensions(data, data->input, input->file + i);
	alloc_map(data);
	fill_map(data->input, input->file + i);
	free_arr(input->file);
	input->file = NULL;
}

void	print_info(t_input *input)
{
	printf("N: {%s}\n", input->n_texture);
	printf("S: {%s}\n", input->s_texture);
	printf("E: {%s}\n", input->e_texture);
	printf("W: {%s}\n", input->w_texture);
	printf("F: {%X}\n", input->f_color);
	printf("C: {%X}\n", input->c_color);
	// printf("Player x: %d\n", input->player_x);
	// printf("Player y: %d\n", input->player_y);
	// printf("Direction: %c\n", input->direction);
	print_map(input->map);
}

void    parsing(t_mlx *data, int argc, char *argv[])
{
	validate_input(argc, argv, data);
	init(data, argv);
	read_file(argv[1], data, 1);
	process_file(data, data->input);
	validate_map(data, data->input->map);
	print_info(data->input);
	free_exit(data, 0);
}
