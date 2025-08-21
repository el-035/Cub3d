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




int     empty_line(char *s)
{
    int i = 0;
    while (s && s[i] && ft_isspace(s[i]))
        i++;
    if (s && s[i] && s[i] != '\n')
        return (0);
    return (1);
}

int    read_file(char *path, t_mlx *data, int process)
{
    int fd;
    int linecount = 0;
    int i = 0;

    fd = open(path, O_RDONLY);
	if (fd < 0)
		parse_error(data, ERR_PERM);
    char *next_line;
	while (1)
	{
		next_line = get_next_line(fd); // add flag
		if (!next_line)
			break ;
        if (!empty_line(next_line))
        {
            linecount++;
            if (process)
            {
                data->input->file[i] = ft_strdup(next_line);
                if (!data->input->file[i])
                    (free(next_line), close(fd), parse_error(data, ERR_ALLOC));
                i++;
            }        
        }
		free(next_line);
	}
	close(fd);
    return (linecount);
}

int    process_pre_map(t_mlx *data, t_input *input, int i)
{
    int type = 0;
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
    if (!ft_strncmp("F", input->file[i], 1))
        type = 5;
    else if (!ft_strncmp("C", input->file[i], 1))
        type = 6;
    if (type > 0)
    {
        process_line(data, input, input->file[i], type);
        input->info_count++;
    }
    return (type);
}

void    process_file(t_mlx *data, t_input *input)
{
    int i = 0;
    while (input->file && input->file[i] && input->info_count < 6)
    {
        if (process_pre_map(data, input, i) == 0)
            parse_error(data, ERR_FILE_CONTENT);
        i++;
    }
    check_map_dimensions(data, data->input, input->file + i);
    alloc_map(data);
    fill_map(data->input, input->file + i);
    free_arr(input->file);
    input->file = NULL;
}

int	main(int argc, char *argv[])
{
    int file_lines;
	t_mlx	data;
 
	validate_input(argc, argv, &data);
    file_lines = read_file(argv[1], &data, 0);
	init(&data, file_lines);
    read_file(argv[1], &data, 1);
    process_file(&data, data.input);
	// validate_map(argv);
	// fill_struct(&data);
    // printf("\nLine length: %d\nline count: %d\n", data.input->line_length, data.input->line_count);
    // print_map(data.input->map);
    free_exit(&data, 0);
}
