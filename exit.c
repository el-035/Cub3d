/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:29:50 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/11/18 19:29:50 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_error(t_mlx *data, char *msg, int free_check)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	if (free_check)
		free_exit(data, 1);
	exit(1);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_textures(t_mlx *data)
{
	if (data->input->n_texture)
	{
		if (data->input->n_texture->file_name)
			free(data->input->n_texture->file_name);
		free(data->input->n_texture);
	}
	if (data->input->s_texture)
	{
		if (data->input->s_texture->file_name)
			free(data->input->s_texture->file_name);
		free(data->input->s_texture);
	}
	if (data->input->e_texture)
	{
		if (data->input->e_texture->file_name)
			free(data->input->e_texture->file_name);
		free(data->input->e_texture);
	}
	if (data->input->w_texture)
	{
		if (data->input->w_texture->file_name)
			free(data->input->w_texture->file_name);
		free(data->input->w_texture);
	}
}

void	free_exit(t_mlx *data, int errnum)
{
	if (!data->input)
		exit(errnum);
	if (data->input->file)
		free_arr(data->input->file);
	if (data->input->map)
		free_arr(data->input->map);
	if (data->input->map_cpy)
		free_arr(data->input->map_cpy);
	free_textures(data);
	if (data->input)
		free(data->input);
}

int	destroy_everything(t_mlx *data)
{
	if (data->input->n_texture->img)
		mlx_destroy_image(data->mlx, data->input->n_texture->img);
	if (data->input->s_texture->img)
		mlx_destroy_image(data->mlx, data->input->s_texture->img);
	if (data->input->e_texture->img)
		mlx_destroy_image(data->mlx, data->input->e_texture->img);
	if (data->input->w_texture->img)
		mlx_destroy_image(data->mlx, data->input->w_texture->img);
	if (data->screen_data->img)
		mlx_destroy_image(data->mlx, data->screen_data->img);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	if (data->screen_data)
		free(data->screen_data);
	if (data->game->ray)
		free(data->game->ray);
	if (data->game)
		free(data->game);
	free(data->mlx);
	free_exit(data, 0);
	exit(0);
}
