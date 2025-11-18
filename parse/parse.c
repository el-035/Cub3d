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


int	add_line(t_mlx *data, char *next_line, int fd, int i)
{
	data->input->file[i] = ft_strdup(next_line);
	if (!data->input->file[i])
		(free(next_line), close(fd), parse_error(data, ERR_ALLOC, 1));
	return (1);
}

int	read_file(char *path, t_mlx *data, int process)
{
	int		fd;
	int		i;
	char	*next_line;
	int		nb_lines = 0;

	i = 0;
	fd = open(path, O_RDONLY);
	int flag = 0;

	if (fd < 0)
		parse_error(data, ERR_PERM, process);
	while (1)
	{
		next_line = get_next_line(fd, &flag); // add flag
		if (flag == 1)
			parse_error(data, ERR_READ, process);
		if (!next_line)
			break ;
		nb_lines++;
		if (process)
			i += add_line(data, next_line, fd, i);
		free(next_line);
	}
	close(fd);
	return (nb_lines);
}

int	process_pre_map(t_mlx *data, t_input *input, int i)
{
	int	type;

	type = 0;
	if (input->info_count < 6)
		input->file[i] = skip_whitespace(input->file[i]);
	if (ft_strncmp("NO", input->file[i], 2) == 0)
		type = 1;
	else if (ft_strncmp("SO", input->file[i], 2) == 0)
		type = 2;
	else if (ft_strncmp("EA", input->file[i], 2) == 0)
		type = 3;
	else if (ft_strncmp("WE", input->file[i], 2) == 0)
		type = 4;
	if (type > 0 && type <= 4 && !ft_isspace(input->file[i][2]))
		parse_error(data, ERR_FILE_CONTENT, 1);
	if (type > 0 && type <= 4)
		parse_texture(data, input, input->file[i], type);
	if (ft_strncmp("F", input->file[i], 1) == 0)
		type = 5;
	else if (ft_strncmp("C", input->file[i], 1) == 0)
		type = 6;
	if ((type == 5 || type == 6) && !ft_isspace(input->file[i][1]))
		parse_error(data, ERR_FILE_CONTENT, 1);
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
			parse_error(data, ERR_FILE_CONTENT, 1);
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
	printf("N: {%s}\n", input->n_texture->file_name);
	printf("S: {%s}\n", input->s_texture->file_name);
	printf("E: {%s}\n", input->e_texture->file_name);
	printf("W: {%s}\n", input->w_texture->file_name);
	printf("F: {%X}\n", input->f_color);
	printf("C: {%X}\n", input->c_color);
	// printf("Player x: %d\n", input->player_x);
	// printf("Player y: %d\n", input->player_y);
	// printf("Direction: %c\n", input->direction);
	print_map(input->map_cpy);
}

void    parsing(t_mlx *data, int argc, char *argv[])
{
	int nb_lines;
	validate_input(argc, argv, data);
	nb_lines = read_file(argv[1], data, 0);
	init(data, nb_lines);
	read_file(argv[1], data, 1);
	process_file(data, data->input);
	validate_map(data, data->input->map);
	dup_map(data);
	flood_fill(data);
	// print_info(data->input);
	// free_exit(data, 0);
}
