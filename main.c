#include "cub3d.h"

int main (void)
{
	t_mlx		data;

	data.input = init_stuff(&data);
	
	//parsing();
	data.test_window = mlx_new_window(data.mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT, "2d test");	//delete
	data.window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	save_img(&data);
	test_start(&data); //delete
	save_screen_buffer(&data, data.game->ray);
	calculate_rays(&data);
	mlx_hook(data.test_window, 17, 0, destroy_everything, &data);	//DEL
	mlx_hook(data.test_window, 2, 1L<<0, &events, &data);			//DEL
	mlx_hook(data.test_window, 3, 1L<<1, &events, &data);			//DEL
	
	mlx_hook(data.window, 17, 0, destroy_everything, &data);
	mlx_hook(data.window, 2, 1L<<0, &events, &data);
	mlx_hook(data.window, 3, 1L<<1, &events, &data);
	mlx_loop(data.mlx);
}
