#include "../cub3d.h"

char	**check_hex_format(t_mlx *data, char *txt)
{
	char	**rgb;
	int		a;
	int		b;

	rgb = ft_split(txt, ',');
	if (!rgb)
		parse_error(data, ERR_ALLOC);
	a = 0;
	while (rgb[a])
	{
		b = 0;
		while (rgb[a][b] && ft_isspace(rgb[a][b]))
			b++;
		while (rgb[a][b] && !ft_isspace(rgb[a][b]) && (rgb[a][b] >= '0'
				&& rgb[a][b] <= '9'))
			b++;
		while (rgb[a][b] && ft_isspace(rgb[a][b]))
			b++;
		if (rgb[a][b])
			(free_arr(rgb), parse_error(data, ERR_INV_COL));
		a++;
	}
	if (a != 3)
		(free_arr(rgb), parse_error(data, ERR_INV_COL));
	return (rgb);
}

char	**extract_color(t_mlx *data, char *line)
{
	int	start;

	start = find_start(line);
	if (start < 0)
		parse_error(data, ERR_NO_COL);
	return (check_hex_format(data, line + start));
}

int	rgb_to_hex_conversion(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	rgb_to_hex(t_mlx *data, char **rgb)
{
	int	hex[3];
	int	i;

	hex[0] = ft_atoi(rgb[0]);
	hex[1] = ft_atoi(rgb[1]);
	hex[2] = ft_atoi(rgb[2]);
	i = 0;
	while (i < 3)
	{
		if (hex[i] < 0 || hex[i] > 255)
			(free_arr(rgb), parse_error(data, ERR_INV_COL));
		i++;
	}
	return (rgb_to_hex_conversion(hex[0], hex[1], hex[2]));
}

void	parse_color(t_mlx *data, t_input *input, char *line, int type)
{
	char	**hex;

	hex = extract_color(data, line);
	if (type == 5)
		input->f_color = rgb_to_hex(data, hex);
	else if (type == 6)
		input->c_color = rgb_to_hex(data, hex);
	free_arr(hex);
}
