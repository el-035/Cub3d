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
	if ((a - 1 >= 0 && map[a-1][b] == ' ') || \
	(a + 1 < data->input->line_count && map[a-1][b] == ' ') ||
	(b - 1 >= 0 && map[a][b-1] == ' ') || \
	(b + 1 < data->input->line_length && map[a][b+1] == ' ') || \
	(b == 0 || a == data->input->line_length))
		parse_error(data, ERR_NO_WALL);
}

void	flood_fill()
{
	;
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
			parse_error(data, ERR_MAP_LINE);
		b = -1;
		while (map[a][++b])
		{
			if (map[a][b] && !is_validchar(map[a][b]))
				parse_error(data, ERR_INV_MAP);
				// (printf("char: [%c]\n%s\n", map[a][b], map[a]), parse_error(data, ERR_INV_MAP));
			if (map[a][b] && is_direction(map[a][b]))
				player_count += set_player_info(data, a, b);
			if (map[a][b] == '0')
				check_walls(data, map, a, b);
		}
	}
	if (player_count != 1)
		parse_error(data, ERR_PLAYER);
}

void	validate_map(t_mlx *data, char **map)
{
	check_chars(data, map);
}
void	check_filename(t_mlx *data, char *file)
{
	if (ft_strncmp(file, ".cub", 5) == 0)
		parse_error(data, ERR_CUB);
	if (!ft_strrchr(file, '.') || ft_strncmp(ft_strrchr(file, '.'), ".cub",
			1) != 0)
		parse_error(data, ERR_FILENAME);
}

void	validate_input(int argc, char *argv[], t_mlx *data)
{
	if (argc != 2)
		parse_error(data, ERR_ARG_NB);
	check_filename(data, argv[1]);
}
