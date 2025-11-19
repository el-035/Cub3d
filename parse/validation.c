/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:29:35 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/11/18 19:29:35 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_walls(t_mlx *data, char **map, int a, int b)
{
	if (map[a][b] != '0')
		return ;
	if ((a == 0 || b == 0 || a == data->input->line_count - 1
			|| b == data->input->line_length)
		|| (a - 1 >= 0 && map[a - 1][b] == ' ')
			|| (a + 1 < data->input->line_count
			&& map[a - 1][b] == ' ') || (b - 1 >= 0 && map[a][b - 1] == ' ')
			|| (b + 1 < data->input->line_length && map[a][b + 1] == ' '))
		parse_error(data, ERR_NO_WALL, 1);
}

void	dup_map(t_mlx *data)
{
	int	i;

	i = 0;
	data->input->map_cpy = ft_calloc(data->input->line_count + 1,
			sizeof(char *));
	if (!data->input->map_cpy)
		parse_error(data, ERR_ALLOC, 1);
	while (data->input->map[i])
	{
		data->input->map_cpy[i] = ft_strdup(data->input->map[i]);
		if (!data->input->map_cpy[i])
			parse_error(data, ERR_ALLOC, 1);
		i++;
	}
}

int	set_player_info(t_mlx *data, int a, int b)
{
	data->input->player_x = b;
	data->input->player_y = a;
	data->input->direction = data->input->map[a][b];
	return (1);
}

void	map_empty_line(t_mlx *data, char **map, int a)
{
	if (empty_line(map[a]))
	{
		while (map[a])
		{
			if (!empty_line(map[a]))
				parse_error(data, ERR_MAP_LINE, 1);
			a++;
		}
	}
}

void	check_chars(t_mlx *data, char **map)
{
	int	player_count;
	int	a;
	int	b;

	player_count = 0;
	a = -1;
	while (map[++a])
	{
		map_empty_line(data, map, a);
		b = -1;
		while (map[a][++b])
		{
			if (map[a][b] && !is_validchar(map[a][b]))
				parse_error(data, ERR_INV_MAP, 1);
			if (map[a][b] && is_direction(map[a][b]))
				player_count += set_player_info(data, a, b);
			if (map[a][b] == '0')
				check_walls(data, map, a, b);
		}
	}
	if (player_count != 1)
		parse_error(data, ERR_PLAYER, 1);
}

void	check_filename(t_mlx *data, char *file)
{
	if (ft_strncmp(file, ".cub", 5) == 0)
		parse_error(data, ERR_CUB, 1);
	if (!ft_strrchr(file, '.') || ft_strncmp(ft_strrchr(file, '.'), ".cub",
			1) != 0)
		parse_error(data, ERR_FILENAME, 1);
}
