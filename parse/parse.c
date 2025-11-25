/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:29:30 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/11/18 19:29:30 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	read_file(char *path, t_mlx *data, int process)
{
	int		fd;
	int		i;
	char	*next_line;
	int		nb_lines;
	int		flag;

	nb_lines = 0;
	i = 0;
	fd = open(path, O_RDONLY);
	flag = 0;
	if (fd < 0)
		parse_error(data, ERR_PERM, process);
	while (1)
	{
		next_line = get_next_line(fd, &flag);
		if (flag == 1)
			(close(fd), parse_error(data, ERR_READ, process));
		if (!next_line)
			break ;
		nb_lines++;
		if (process)
			i += add_line(data, next_line, fd, i);
		free(next_line);
	}
	return (close(fd), nb_lines);
}

int	determine_type(char *direction)
{
	int	type;

	type = 0;
	if (ft_strncmp("NO", direction, 2) == 0)
		type = 1;
	else if (ft_strncmp("SO", direction, 2) == 0)
		type = 2;
	else if (ft_strncmp("EA", direction, 2) == 0)
		type = 3;
	else if (ft_strncmp("WE", direction, 2) == 0)
		type = 4;
	return (type);
}

int	process_pre_map(t_mlx *data, t_input *input, int i)
{
	int	type;

	if (input->info_count < 6)
	{
		input->file[i] = skip_whitespace(input->file[i]);
		if (!input->file[i])
			parse_error(data, ERR_ALLOC, 1);
	}
	type = determine_type(input->file[i]);
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
	while (input->file && input->file[i] && (input->info_count < 6
			|| empty_line(input->file[i])))
	{
		if (!empty_line(input->file[i]))
		{
			if (process_pre_map(data, input, i) == 0)
				parse_error(data, ERR_FILE_CONTENT, 1);
		}
		i++;
	}
	if (input->info_count < 6)
		parse_error(data, ERR_NO_INFO, 1);
	check_map_dimensions(data, data->input, input->file + i);
	alloc_map(data);
	fill_map(data->input, input->file + i);
	free_arr(input->file);
	input->file = NULL;
}

void	parsing(t_mlx *data, int argc, char *argv[])
{
	int	nb_lines;

	(void)argc;
	check_filename(data, argv[1]);
	nb_lines = read_file(argv[1], data, 0);
	init(data, nb_lines);
	read_file(argv[1], data, 1);
	process_file(data, data->input);
	check_chars(data, data->input->map);
	dup_map(data);
	flood_fill(data);
}
