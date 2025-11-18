/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:34:03 by efittant          #+#    #+#             */
/*   Updated: 2025/11/18 18:36:56 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	side_dist_x(t_game *game, t_input *input)
{
	game->ray->x += game->ray->step_x;
	if (input->map[game->ray->y][game->ray->x] == '1')
	{
		game->ray->distance = game->ray->side_dist_x;
		if (game->ray->ray_dir_x < 0)
			game->ray->wall = W;
		else
			game->ray->wall = E;
		return (1);
	}
	game->ray->side_dist_x += game->ray->delta_dist_x;
	return (0);
}

int	side_dist_y(t_game *game, t_input *input)
{
	game->ray->y += game->ray->step_y;
	if (input->map[game->ray->y][game->ray->x] == '1')
	{
		if (game->ray->ray_dir_y < 0)
			game->ray->wall = N;
		else
			game->ray->wall = S;
		game->ray->distance = game->ray->side_dist_y;
		return (1);
	}
	game->ray->side_dist_y += game->ray->delta_dist_y;
	return (0);
}

void	wall_height(t_ray *ray, t_texture *img)
{
	ray->wall_height = (WINDOW_HEIGHT) / ray->distance;
	ray->wall_start = (WINDOW_HEIGHT - ray->wall_height) / 2;
	if (ray->wall_start < 0)
	{
		ray->img_start = (abs(ray->wall_start)) * img->height
			/ ray->wall_height;
		ray->wall_height += ray->wall_start;
		ray->wall_start = 0;
	}
	else
		ray->img_start = 0;
	ray->wall_end = (WINDOW_HEIGHT + ray->wall_height) / 2;
	if (ray->wall_end >= WINDOW_HEIGHT)
		ray->wall_end = WINDOW_HEIGHT;
}

t_texture	*wall_side(t_mlx *data, t_ray *ray)
{
	t_texture	*wall;

	wall = NULL;
	if (ray->wall == N || ray->wall == S)
	{
		ray->x_pos = (data->game->pos_x + ray->ray_dir_x * ray->distance);
		wall = data->input->n_texture;
		if (ray->wall == S)
			wall = data->input->s_texture;
	}
	if (ray->wall == W || ray->wall == E)
	{
		ray->x_pos = (data->game->pos_y + ray->ray_dir_y * ray->distance);
		wall = data->input->w_texture;
		if (ray->wall == E)
			wall = data->input->e_texture;
	}
	ray->x_pos -= floor(ray->x_pos);
	wall_height(ray, wall);
	return (wall);
}
