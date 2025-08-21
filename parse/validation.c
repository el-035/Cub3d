#include "../cub3d.h"

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

void	check_filename(t_mlx *data, char *file)
{
	if (ft_strncmp(file, ".cub", 5) == 0)
		parse_error(data, ERR_CUB);
	if (!ft_strrchr(file, '.') || ft_strncmp(ft_strrchr(file, '.'), ".cub", 1) != 0)
		parse_error(data, ERR_FILENAME);
}

void	validate_input(int argc, char *argv[], t_mlx *data)
{
	if (argc != 2)
		parse_error(data, ERR_ARG_NB);
	check_filename(data, argv[1]);
}