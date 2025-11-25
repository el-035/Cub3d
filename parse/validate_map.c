/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:21:57 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/11/19 15:21:57 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	fill_grid(t_mlx *data, int x, int y, int *open)
{
	if (y < 0 || x < 0 || (data->input->map_cpy[y]
			&& x >= ft_strlen(data->input->map_cpy[y]))
		|| y >= data->input->line_count || data->input->map_cpy[y][x] == ' ')
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
	// fill_grid(data, x - 1, y - 1, open);
	// fill_grid(data, x + 1, y + 1, open);
	// fill_grid(data, x - 1, y + 1, open);
	// fill_grid(data, x + 1, y - 1, open);
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
			if (data->input->map_cpy[y][x] == 'N'
				|| data->input->map_cpy[y][x] == 'S'
				|| data->input->map_cpy[y][x] == 'E'
				|| data->input->map_cpy[y][x] == 'W')
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
