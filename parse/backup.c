// #include "../cub3d.h"

// #include "../cub3d.h"

// // open, close, read, write,
// // printf, malloc, free, perror,
// // strerror, exit, gettimeofday



// // NO, SO, WE, EA and path
// // F/C and valid color (range 0-255)
// // multiple lines between input type OK
// // no empty lines in map content
// // map has to be last
// // check textures exist and have permissions

// void    check_line(t_mlx *data, char *line)
// {
//     int type = 0;

//         if (!ft_strncmp("\n", line, 1))
//             return ;
//         if (data->input->info_count < 6)
//             line = skip_whitespace(line);
//         if (!ft_strncmp("NO", line, 2))
//             type = 1;
//         else if (!ft_strncmp("SO", line, 2))
//             type = 2;
//         else if (!ft_strncmp("EA", line, 2))
//             type = 3;
//         else if (!ft_strncmp("WE", line, 2))
//             type = 4;
//         if (!ft_strncmp("F", line, 1))
//             type = 5;
//         else if (!ft_strncmp("C", line, 1))
//             type = 6;
//         if (type > 0)
//         {
//             if (type > 0 && data->input->read_count == 1)
//             {
//             if (type < 5)
//                 line = skip_whitespace(line + 2);
//             else
//                 line = skip_whitespace(line + 1);
//             process_line(data, data->input, line, type);
//             }
//             data->input->info_count++;
//             return;
//         }
//     if (data->input->read_count == 1)
//         process_map(data, data->input, line);
//     else if (data->input->info_count == 6 && data->input->read_count == 0)
//         check_dimensions(data, data->input, line);
//     else
//         (printf("line: %s\n, info count: %i\n", line, data->input->info_count), free(line), parse_error(data, ERR_FILE_CONTENT));
// }


// void    process_file(char *path, t_mlx *data)
// {
//     alloc_map(data);
//     read_file(path, data);
// }

// void    read_file(char *path, t_mlx *data)
// {
//     int fd;

//     fd = open(path, O_RDONLY);
// 	if (fd < 0)
// 		parse_error(data, ERR_PERM);
//     char *next_line;
// 	while (1)
// 	{
// 		next_line = get_next_line(fd); // add flag
// 		if (!next_line)
// 			break ;
//         check_line(data, next_line);
// 		free(next_line);
// 	}
// 	close(fd);
// }

// int	main(int argc, char *argv[])
// {
// 	t_mlx	data;

// 	init(&data);
// 	validate_input(argc, argv, &data);
//     read_file(argv[1], &data);
//     data.input->read_count = 1;
//     process_file(argv[1], &data);
// 	// validate_map(argv);
// 	// fill_struct(&data);
//     printf("\nLine length: %d\nline count: %d\n", data.input->line_length, data.input->line_count);
//     print_map(data.input->map);
//     free_exit(&data, 0);
// }

// #include "../cub3d.h"

// void	init(t_mlx *data)
// {
// 	data->input = malloc(sizeof(t_input));
// 	if (!data->input)
// 		parse_error(data, ERR_ALLOC);
// 	data->input->map = NULL;
// 	data->input->n_texture = NULL;
// 	data->input->s_texture = NULL;
// 	data->input->e_texture = NULL;
// 	data->input->w_texture = NULL;
// 	data->mlx = NULL;
// 	data->window = NULL;
// 	data->input->line_length = 0;
// 	data->input->line_count = 0;
//     data->input->info_count = 0;
//     data->input->read_count = 0;
// }

// char    *extract_filename(t_mlx *data, char *line)
// {
//     int i = 0;
//     while (line && line[i] && !ft_isspace(line[i]) && line[i] != '\n')
//         i++;
//     int a = 0;
//     while (line && line[i+a] && ft_isspace(line[i+a]))
//         a++;
//     if (a == 0)
//         return(line);
//     if (line && line[i+a] && !ft_isspace(line[i+a]) && line[i] != '\n')
//         (parse_error(data, ERR_EXTRA_CHAR));
//     char *new = ft_calloc(i + 1, sizeof(char));
//     if (!new)
//         (free(line), parse_error(data, ERR_ALLOC));
//     ft_strlcpy(new, line, i+1);
//     free(line);
//     return (new);

// }

// void    process_line(t_mlx *data, t_input *input, char *line, int type)
// {
//     line = extract_filename(data, line);
//     if (type == 1)
//         input->n_texture = ft_strdup(line);
//     else if (type == 2)
//         input->s_texture = ft_strdup(line);
//     else if (type == 3)
//         input->e_texture = ft_strdup(line);
//     else if (type == 4)
//         input->w_texture = ft_strdup(line);
//     // set colors to hex
//     // else if (type == 5)
//     //     input->f_color = ft_strdup(line);
//     // else if (type == 6)
//     //     input->c_color = ft_strdup(line);
// }

// // set colors to hex
// // fill struct
// void	fill_struct(t_mlx *data)
// {
//     (void)data;
// }

// #include "../cub3d.h"

// void check_dimensions(t_mlx *data, t_input *input, char *line)
// {
//     int i = 0;
//     if (!ft_strncmp("\n", line, 1))
//         (free(line), parse_error(data, ERR_MAP_LINE));
//     while (line && line[i])
//         i++;
//     if (i > input->line_length)
//         input->line_length = i;
//     input->line_count++;
// }

// void    process_map(t_mlx *data, t_input *input, char *line)
// {
//     int i = 0;
//     int len;
//     while (input->map && input->map[i] && input->map[i][0])
//         i++;
//     len = ft_strlen(line);
//     if (len > 0 && line[len-1] == '\n')
//         len--;
//     ft_strlcpy(input->map[i], line, len + 1);
//     (void)data;
// }

// void    alloc_map(t_mlx *data)
// {
//     int i = 0;
//     data->input->map = calloc(data->input->line_count + 1, sizeof(char *));
//     if (!data->input->map)
//         parse_error(data, ERR_ALLOC);
//     while (i < data->input->line_count)
//     {
//         data->input->map[i] = calloc(data->input->line_length + 1, sizeof(char));
//         if (!data->input->map[i])
//             parse_error(data, ERR_ALLOC);
//         i++;
//     }
// }

// #include "../cub3d.h"

// // surrounded by walls
// // 6 valid chars (0, 1, NSEW once)
// // check if player can move
// // ◦ Except for the map,
// 	// each type of information from an element can be separated
// // by one or more spaces
// // -> check no extra spaces that are not on the outside

// void	validate_map(char *argv[])
// {
//     (void)argv;
// }

// void	check_filename(t_mlx *data, char *file)
// {
// 	if (ft_strncmp(file, ".cub", 5) == 0)
// 		parse_error(data, ERR_CUB);
// 	if (!ft_strrchr(file, '.') || ft_strncmp(ft_strrchr(file, '.'), ".cub", 1) != 0)
// 		parse_error(data, ERR_FILENAME);
// }

// void	validate_input(int argc, char *argv[], t_mlx *data)
// {
// 	if (argc != 2)
// 		parse_error(data, ERR_ARG_NB);
// 	check_filename(data, argv[1]);
// }