/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:40:20 by efittant          #+#    #+#             */
/*   Updated: 2025/11/25 18:26:23 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_stuff(t_mlx *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (parse_error(data, MLX_FAIL, 1));
	data->game = malloc(sizeof(t_game));
	if (!data->game)
		return (parse_error(data, ERR_ALLOC, 1));
	data->game->ray = malloc(sizeof(t_ray));
	if (!data->game->ray)
		return (parse_error(data, ERR_ALLOC, 1));
	data->screen_data = malloc(sizeof(t_texture));
	if (!data->screen_data)
		return (parse_error(data, ERR_ALLOC, 1));
	ft_memset(data->screen_data, 0, sizeof(t_texture));
	ft_memset(data->keys, 0, sizeof(data->keys));
}

int	save_img_ew(t_mlx *data, t_texture *e_texture, t_texture *w_texture)
{
	e_texture->img = mlx_xpm_file_to_image(data->mlx, e_texture->file_name,
			&e_texture->width, &e_texture->height);
	if (!e_texture->img)
		return (parse_error(data, MLX_FAIL, 1), 1);
	e_texture->data = mlx_get_data_addr(e_texture->img,
			&e_texture->bits_per_pixel, &e_texture->size_line,
			&e_texture->endian);
	if (!e_texture->data)
		return (parse_error(data, MLX_FAIL, 1), 1);
	w_texture->img = mlx_xpm_file_to_image(data->mlx, w_texture->file_name,
			&w_texture->width, &w_texture->height);
	if (!w_texture->img)
		return (parse_error(data, MLX_FAIL, 1), 1);
	w_texture->data = mlx_get_data_addr(w_texture->img,
			&w_texture->bits_per_pixel, &w_texture->size_line,
			&w_texture->endian);
	if (!w_texture->data)
		return (parse_error(data, MLX_FAIL, 1), 1);
	return (0);
}

int	save_screen(t_mlx *data, t_texture *screen_data)
{
	screen_data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!screen_data->img)
		return (parse_error(data, MLX_FAIL, 1), 1);
	screen_data->data = mlx_get_data_addr(screen_data->img,
			&screen_data->bits_per_pixel, &screen_data->size_line,
			&screen_data->endian);
	if (!screen_data->data)
		return (parse_error(data, MLX_FAIL, 1), 1);
	return (0);
}

int	save_img_ns(t_mlx *data, t_texture *n_texture, t_texture *s_texture)
{
	n_texture->img = mlx_xpm_file_to_image(data->mlx, n_texture->file_name,
			&n_texture->width, &n_texture->height);
	if (!n_texture->img)
		return (parse_error(data, MLX_FAIL, 1), 1);
	n_texture->data = mlx_get_data_addr(n_texture->img,
			&n_texture->bits_per_pixel, &n_texture->size_line,
			&n_texture->endian);
	if (!n_texture->data)
		return (parse_error(data, MLX_FAIL, 1), 1);
	s_texture->img = mlx_xpm_file_to_image(data->mlx, s_texture->file_name,
			&s_texture->width, &s_texture->height);
	if (!s_texture->img)
		return (parse_error(data, MLX_FAIL, 1), 1);
	s_texture->data = mlx_get_data_addr(s_texture->img,
			&s_texture->bits_per_pixel, &s_texture->size_line,
			&s_texture->endian);
	if (!s_texture->data)
		return (parse_error(data, MLX_FAIL, 1), 1);
	return (0);
}

void	init_game(t_mlx *mlx)
{
	mlx->game->pos_x = mlx->input->player_x + 0.5;
	mlx->game->pos_y = mlx->input->player_y + 0.5;
	if (mlx->input->direction == 'S' || mlx->input->direction == 'N')
	{
		mlx->game->dir_x = 0;
		mlx->game->dir_y = 1;
		if (mlx->input->direction == 'N')
			mlx->game->dir_y = -1;
	}
	else if (mlx->input->direction == 'E' || mlx->input->direction == 'W')
	{
		mlx->game->dir_x = 1;
		mlx->game->dir_y = 0;
		if (mlx->input->direction == 'W')
			mlx->game->dir_x = -1;
	}
	mlx->game->angle = atan2(mlx->game->dir_y, mlx->game->dir_x);
}
