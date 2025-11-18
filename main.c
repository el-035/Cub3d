/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efittant <efittant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:47:07 by efittant          #+#    #+#             */
/*   Updated: 2025/11/18 18:47:18 by efittant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	save_img(t_mlx *data, t_input *input)
{
	if (save_img_ns(data, input->n_texture, input->s_texture) == 1)
		return (1);
	if (save_img_ew(data, input->e_texture, input->w_texture) == 1)
		return (1);
	if (save_screen(data, data->screen_data) == 1)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	data;

	if (argc != 2)
		return (parse_error(&data, ERR_ARG, 0), 1);
	parsing(&data, argc, argv);
	init_stuff(&data);
	data.window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3d");
	if (!data.window)
		return (parse_error(&data, MLX_FAIL, 1), 1);
	save_img(&data, data.input);
	init_game(&data);
	save_screen_buffer(&data, data.game->ray);
	mlx_put_image_to_window(data.mlx, data.window, data.screen_data->img, 0, 0);
	mlx_hook(data.window, 17, 0, destroy_everything, &data);
	mlx_hook(data.window, 2, 1L << 0, &events, &data);
	mlx_hook(data.window, 3, 1L << 1, &events, &data);
	mlx_loop(data.mlx);
}
