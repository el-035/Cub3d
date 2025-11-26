/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:20:51 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/11/19 15:20:51 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_validchar(char c)
{
	return (c == '\r' || c == ' ' || c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

int	is_direction(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	add_line(t_mlx *data, char *next_line, int fd, int i)
{
	data->input->file[i] = ft_strdup(next_line);
	if (!data->input->file[i])
		(free(next_line), close(fd), parse_error(data, ERR_ALLOC, 1));
	return (1);
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
		while (rgb[i][a + len] && (rgb[i][a + len] == '0'
			|| ft_isspace(rgb[i][a + len])))
			a++;
		if (rgb[i][a] == '-')
			(free_arr(rgb), parse_error(data, ERR_NEG, 1));
		while (rgb[i][a + len])
		{
			if (ft_isdigit(rgb[i][a + len]))
				len++;
			else
				a++;
		}
		if (len > 3)
			(free_arr(rgb), parse_error(data, ERR_INV_COL, 1));
		i++;
	}
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
