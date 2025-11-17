#include "../cub3d.h"

// surrounded by walls
// 6 valid chars (0, 1, NSEW once)
// check if player can move
// ◦ Except for the map,
// each type of information from an element can be separated
// by one or more spaces
// -> check no extra spaces that are not on the outside

int	is_validchar(char c)
{
	return (c == '\r' || c == ' ' || c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

int	is_direction(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	check_walls(t_mlx *data, char **map, int a, int b)
{
	if (map[a][b] != '0')
		return ;
	if ((a == 0 || b == 0 || a == data->input->line_count - 1 || b == data->input->line_length) || \
	(a - 1 >= 0 && map[a-1][b] == ' ') || \
	(a + 1 < data->input->line_count && map[a-1][b] == ' ') ||
	(b - 1 >= 0 && map[a][b-1] == ' ') || \
	(b + 1 < data->input->line_length && map[a][b+1] == ' '))
		parse_error(data, ERR_NO_WALL, 1);
}

void	dup_map(t_mlx *data) // malloc protections
{
	data->input->map_cpy = ft_calloc(data->input->line_count + 1, sizeof(char *));
	int i = 0;
	while (data->input->map[i])
	{
		data->input->map_cpy[i] = ft_strdup(data->input->map[i]);
		i++;
	}
}

void	fill_grid(t_mlx *data, int x, int y, int *open)
{
	if (y < 0 || x < 0 || (data->input->map_cpy[y] && x >= ft_strlen(data->input->map_cpy[y])) || y >= data->input->line_count || data->input->map_cpy[y][x] == ' ') // correct to check for out of bounds here?
	{
		(*open)++;
		return ;
	}
	if (data->input->map_cpy[y][x] == '1' || data->input->map_cpy[y][x] == 'F')
		return ;
	data->input->map_cpy[y][x] = 'F';
	fill_grid(data, x + 1, y, open);
	fill_grid(data, x - 1, y, open);
	fill_grid(data, x, y + 1, open);
	fill_grid(data, x, y - 1, open);
	// diagonals
	fill_grid(data, x - 1, y - 1, open);
	fill_grid(data, x + 1, y + 1, open);
	fill_grid(data, x - 1, y + 1, open);
	fill_grid(data, x + 1, y - 1, open);
}

void	flood_fill(t_mlx *data)
{
	int	x;
	int	y;
	int	open;

	y = 0;
	open = 0;

	while (data->input->map_cpy[y])
	{
		x = 0;
		while (data->input->map_cpy[y][x])
		{
			if (data->input->map_cpy[y][x] == 'N' || data->input->map_cpy[y][x] == 'S' || data->input->map_cpy[y][x] == 'E' || data->input->map_cpy[y][x] == 'W')
			{
				fill_grid(data, x, y, &open);
				if (open)
					parse_error(data, ERR_NO_WALL, 1);
				return ;
			}
			x++;
		}
		y++;
	}
}

int	set_player_info(t_mlx *data, int a, int b)
{
	data->input->player_x = b;
	data->input->player_y = a;
	data->input->direction = data->input->map[a][b];
	return (1);
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
		if (empty_line(map[a]))
			parse_error(data, ERR_MAP_LINE, 1);
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
	if (player_count > 1)
		parse_error(data, ERR_PLAYER, 1);
}

void	validate_map(t_mlx *data, char **map)
{
	check_chars(data, map);
}
void	check_filename(t_mlx *data, char *file)
{
	if (ft_strncmp(file, ".cub", 5) == 0)
		parse_error(data, ERR_CUB, 1);
	if (!ft_strrchr(file, '.') || ft_strncmp(ft_strrchr(file, '.'), ".cub",
			1) != 0)
		parse_error(data, ERR_FILENAME, 1);
}

void	validate_input(int argc, char *argv[], t_mlx *data)
{
	if (argc != 2)
		parse_error(data, ERR_ARG_NB, 1);
	check_filename(data, argv[1]);
}
