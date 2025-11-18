/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:50:46 by efittant          #+#    #+#             */
/*   Updated: 2025/11/18 19:12:03 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_wall(t_mlx *data, int y, int x, t_texture *wall)
{
	int	pos;
	int	img_pos;
	int	text_y;
	int	text_x;

	pos = y * data->screen_data->size_line + x
		* (data->screen_data->bits_per_pixel / 8);
	text_y = data->game->ray->img_start + ((y - data->game->ray->wall_start)
			* (wall->height - data->game->ray->img_start))
		/ data->game->ray->wall_height;
	text_x = (int)(data->game->ray->x_pos * wall->height) % wall->height;
	if (text_y >= wall->size_line)
		text_y = wall->size_line - 1;
	if (text_y < 0)
		text_y = 0;
	img_pos = text_y * wall->size_line + text_x * (wall->bits_per_pixel / 8);
	*(int *)(data->screen_data->data + pos) = *(int *)(wall->data + img_pos);
}

void	save_screen_buffer(t_mlx *data, t_ray *ray)
{
	int			y;
	int			x;
	int			pos;
	t_texture	*wall;

	x = -1;
	while (++x < WINDOW_WIDTH)
	{
		y = 0;
		wall = find_dir(data, data->game, ray, x);
		while (y < ray->wall_start)
		{
			pos = y++*data->screen_data->size_line + x
				* (data->screen_data->bits_per_pixel / 8);
			*(int *)(data->screen_data->data + pos) = data->input->c_color;
		}
		while (y < ray->wall_end && y < WINDOW_HEIGHT)
			put_wall(data, y++, x, wall);
		while (y < WINDOW_HEIGHT)
		{
			pos = y++*data->screen_data->size_line + x
				* (data->screen_data->bits_per_pixel / 8);
			*(int *)(data->screen_data->data + pos) = data->input->f_color;
		}
	}
}
