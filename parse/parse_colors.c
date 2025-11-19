/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:29:22 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/11/18 19:29:22 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**check_hex_format(t_mlx *data, char **rgb)
{
	int		a;
	int		b;
	int		color_present;

	a = 0;
	while (rgb[a])
	{
		b = 0;
		while (rgb[a][b] && ft_isspace(rgb[a][b]))
			b++;
		color_present = b;
		while (rgb[a][b] && !ft_isspace(rgb[a][b]) &&
		(rgb[a][b] >= '0' && rgb[a][b] <= '9'))
			b++;
		if (color_present == b)
			(free_arr(rgb), parse_error(data, ERR_INV_COL, 1));
		while (rgb[a][b] && ft_isspace(rgb[a][b]))
			b++;
		if (rgb[a][b])
			(free_arr(rgb), parse_error(data, ERR_INV_COL, 1));
		a++;
	}
	if (a != 3)
		(free_arr(rgb), parse_error(data, ERR_INV_COL, 1));
	return (rgb);
}

void	check_overflow(t_mlx *data, char **rgb)
{
	int	i;
	int	a;
	int	len;

	i = 0;
	while (rgb[i])
	{
		a = 0;
		len = 0;
		while (rgb[i][a+len])
		{
			if (ft_isdigit(rgb[i][a+len]))
				len++;
			else
				a++;
		}
		if (len > 3)
			(free_arr(rgb), parse_error(data, ERR_OVERFLOW, 1));
		i++;
	}
}

char	**extract_color(t_mlx *data, char *line)
{
	int		start;
	char	**rgb;

	start = find_start(line);
	if (start < 0)
		parse_error(data, ERR_NO_COL, 1);
	rgb = ft_split(line + start, ',');
	if (!rgb)
		parse_error(data, ERR_ALLOC, 1);
	check_overflow(data, rgb);
	return (check_hex_format(data, rgb));
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
			(free_arr(rgb), parse_error(data, ERR_INV_COL, 1));
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
