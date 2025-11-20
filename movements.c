/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:50:10 by efittant          #+#    #+#             */
/*   Updated: 2025/11/18 18:50:11 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_mlx *mlx, double x, double y)
{
	double	xx;
	double	yy;
	double	angle;
	double	rad;

	angle = 0;
	rad = 0.04;
	while (angle < (2 * M_PI))
	{
		xx = x + (cos(angle) * rad);
		yy = y + (sin(angle) * rad);
		angle += (M_PI / 4);
		if (mlx->input->map[(int)yy][(int)xx] == '1')
			return (1);
	}
	return (0);
}

int	up_down(int key, t_mlx *mlx)
{
	if (key == UP)
	{
		if (is_wall(mlx, (mlx->game->pos_x + mlx->game->dir_x * MOVEMENT),
				(mlx->game->pos_y + mlx->game->dir_y * MOVEMENT)) == 1)
			return (0);
		mlx->game->pos_x += mlx->game->dir_x * MOVEMENT;
		mlx->game->pos_y += mlx->game->dir_y * MOVEMENT;
		save_screen_buffer(mlx, mlx->game->ray);
		mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->screen_data->img, 0,
			0);
	}
	if (key == DOWN)
	{
		if (is_wall(mlx, (mlx->game->pos_x - mlx->game->dir_x * MOVEMENT),
				(mlx->game->pos_y - mlx->game->dir_y * MOVEMENT)) == 1)
			return (0);
		mlx->game->pos_x -= mlx->game->dir_x * MOVEMENT;
		mlx->game->pos_y -= mlx->game->dir_y * MOVEMENT;
		save_screen_buffer(mlx, mlx->game->ray);
		mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->screen_data->img, 0,
			0);
	}
	return (0);
}

int	left_right(int key, t_mlx *mlx)
{
	if (key == LEFT)
	{
		if (is_wall(mlx, (mlx->game->pos_x - (-mlx->game->dir_y) * MOVEMENT),
				(mlx->game->pos_y - mlx->game->dir_x * MOVEMENT)) == 1)
			return (0);
		mlx->game->pos_x -= (-mlx->game->dir_y) * MOVEMENT;
		mlx->game->pos_y -= mlx->game->dir_x * MOVEMENT;
		save_screen_buffer(mlx, mlx->game->ray);
		mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->screen_data->img, 0,
			0);
	}
	if (key == RIGHT)
	{
		if (is_wall(mlx, (mlx->game->pos_x + (-mlx->game->dir_y) * MOVEMENT),
				(mlx->game->pos_y + mlx->game->dir_x * MOVEMENT)) == 1)
			return (0);
		mlx->game->pos_x += (-mlx->game->dir_y) * MOVEMENT;
		mlx->game->pos_y += mlx->game->dir_x * MOVEMENT;
		save_screen_buffer(mlx, mlx->game->ray);
		mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->screen_data->img, 0,
			0);
	}
	return (0);
}

int	rotate(int key, t_mlx *mlx)
{
	if (key == ROT_LEFT)
	{
		mlx->game->angle -= ROTATION;
		mlx->game->dir_x = cos(mlx->game->angle);
		mlx->game->dir_y = sin(mlx->game->angle);
		save_screen_buffer(mlx, mlx->game->ray);
		mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->screen_data->img, 0,
			0);
	}
	if (key == ROT_RIGHT)
	{
		mlx->game->angle += ROTATION;
		mlx->game->dir_x = cos(mlx->game->angle);
		mlx->game->dir_y = sin(mlx->game->angle);
		save_screen_buffer(mlx, mlx->game->ray);
		mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->screen_data->img, 0,
			0);
	}
	return (0);
}
