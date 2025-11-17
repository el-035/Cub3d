#include "cub3d.h"

int main (int argc, char **argv)
{
	t_mlx		data;

	if (argc != 2)
		return (1); //ERROR

	parsing(&data, argc, argv);
	init_stuff(&data);
	data.window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	save_img(&data);
	init_game(&data);
	save_screen_buffer(&data, data.game->ray);
	mlx_put_image_to_window(data.mlx, data.window, data.screen_data->img, 0, 0);
	mlx_hook(data.window, 17, 0, destroy_everything, &data);
	mlx_hook(data.window, 2, 1L<<0, &events, &data);
	mlx_hook(data.window, 3, 1L<<1, &events, &data);
	mlx_loop(data.mlx);
	free_exit(&data, 0);
}
