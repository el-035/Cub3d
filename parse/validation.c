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

void	validate_map(t_mlx *data, char **map)
{
	int	player;
	int	a;
	int	b;

	player = 0;
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
			{
				player++;
				data->input->player_x = b;
				data->input->player_y = a;
				data->input->direction = map[a][b];
			}
		}
	}
	if (player != 1)
		parse_error(data, ERR_PLAYER);
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
