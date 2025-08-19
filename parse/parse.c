#include "../cub3d.h"

// open, close, read, write,
// printf, malloc, free, perror,
// strerror, exit, gettimeofday

void	check_filename(t_mlx *data, char *file)
{
	if (ft_strncmp(file, ".cub", 5) == 0)
		parse_error(data, ERR_CUB);
	if (!ft_strrchr(file, '.') || ft_strncmp(ft_strrchr(file, '.'), ".cub", 1) != 0)
		parse_error(data, ERR_FILENAME);
}

// NO, SO, WE, EA and path
// F/C and valid color (range 0-255)
// multiple lines between input type OK
// no empty lines in map content
// map has to be last
// check textures exist and have permissions

// only count map dimensions here


// void    check_map()
// {
//     int		fd;
// 	int		len;
// 	int		max_len;
// 	int		read_check;
// 	char	c;

//     fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 		parse_error(data, ERR_PERM);
// 	len = 0;
// 	max_len = 0;
// 	while (1)
// 	{
// 		read_check = read(fd, &c, 1);
// 		if (read_check < 0)
// 			(close(fd), parse_error(data, ERR_READ));
// 		else if (read_check == 0)
// 			break ;
// 		len++;
// 		if (c == '\n')
// 		{
// 			data->input->line_count++;
// 			if (len > max_len)
// 				max_len = len;
// 			len = 0;
// 		}
// 	}
//     close(fd);
// 	data->input->line_length = max_len;
// }

void check_dimensions(t_mlx *data, t_input *input, char *line)
{
    int i = 0;
    if (!ft_strncmp("\n", line, 1))
        (free(line), parse_error(data, ERR_MAP_LINE));
    while (line && line[i])
        i++;
    if (i > input->line_length)
        input->line_length = i;
    input->line_count++;
}

 int     ft_isspace(int c)
 {
    return ((c >= 9 && c <= 13) || c == ' ');
 }

char *skip_whitespace(char *line)
{
    while (line && *line && ft_isspace(*line))
        line++;
    return (line);
}

void    process_line(t_mlx *data, char *line)
{
    (void)data;
    (void)line;
}

void    process_map(t_mlx *data, char *line)
{
    (void)data;
    (void)line;
}

void    check_line(t_mlx *data, char *line, int *sections, int process)
{
    int type = 0;

    if (!ft_strncmp("\n", line, 1))
        return ;
    if (*sections < 6)
        line = skip_whitespace(line);
    if (!ft_strncmp("NO", line, 2))
        type = 1;
    else if (!ft_strncmp("SO", line, 2))
        type = 2;
    else if (!ft_strncmp("EA", line, 2))
        type = 3;
    else if (!ft_strncmp("WE", line, 2))
        type = 4;
    if (!ft_strncmp("F", line, 1))
        type = 5;
    else if (!ft_strncmp("H", line, 1))
        type = 6;
    if (type > 0)
    {
        if (type < 5)
            line = skip_whitespace(line + 2);
        else
            line = skip_whitespace(line + 1);
        sections++;
        if (process)
            process_line(data, line);
        return;
    }
    if (process)
        process_map(data, line);
    else
        check_dimensions(data, data->input, line);
    (void)sections;
}



void    read_file(char *path, t_mlx *data, int process)
{
    int fd;
    int sections = 0;

    fd = open(path, O_RDONLY);
	if (fd < 0)
		parse_error(data, ERR_PERM);
    char *next_line;
	while (1)
	{
		next_line = get_next_line(fd); // add flag
		if (!next_line)
			break ;
        // printf("%s", next_line);
        check_line(data, next_line, &sections, process);
		free(next_line);
	}
	close(fd);
}

void	validate_input(int argc, char *argv[], t_mlx *data)
{

	if (argc != 2)
		parse_error(data, ERR_ARG_NB);
	check_filename(data, argv[1]);
	
}

void	init(t_mlx *data)
{
	data->input = malloc(sizeof(t_input));
	if (!data->input)
		parse_error(data, ERR_ALLOC);
	data->input->input_map = NULL;
	data->input->n_texture = NULL;
	data->input->s_texture = NULL;
	data->input->e_texture = NULL;
	data->input->w_texture = NULL;
	data->mlx = NULL;
	data->window = NULL;
	data->input->line_length = 0;
	data->input->line_count = 0;
}

// surrounded by walls
// 6 valid chars (0, 1, NSEW once)
// check if player can move
// ◦ Except for the map,
	// each type of information from an element can be separated
// by one or more spaces
// -> check no extra spaces that are not on the outside

void	validate_map(char *argv[])
{
    (void)argv;
}

// set colors to hex
// fill struct

void	fill_struct(t_mlx *data)
{
    (void)data;
}

int	main(int argc, char *argv[])
{
	t_mlx	data;

	init(&data);
	validate_input(argc, argv, &data);
    read_file(argv[1], &data, 0);
    process_file(argv[1], &data);
	// validate_map(argv);
	// fill_struct(&data);
    printf("\nLine length: %d\nline count: %d\n", data.input->line_length, data.input->line_count);
    free_exit(&data, 0);
}
