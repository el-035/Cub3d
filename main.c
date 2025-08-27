/*  FUNCTIONS ALLOWED
• open, close, read, write, printf, malloc, free, perror, strerror, exit, gettimeofday.
• All functions of the math library (-lm man man 3 math).
• gettimeofday()
• All functions of the MinilibX library. */

#include "cub3d.h"

int main (void)
{
	t_mlx		data;
	t_input		*input;
	int			width;
	int			heignt;
	data.mlx = mlx_init();
	if (!data.mlx)
		return 1; //errors("Allocation failed", data);
	data.game = malloc(sizeof(t_game));
	data.game->ray = malloc(sizeof(t_ray));
	input = create_hardcoded_map();	//delete
	input->n_texture = mlx_xpm_file_to_image(data.mlx, "test_images/purple_N.png", &width, &heignt); //delete
	data.input = input;
	data.window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	data.test_window = mlx_new_window(data.mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT, "2d test");	//delete
	test_start(&data); //delete
	mlx_hook(data.test_window, 17, 0, destroy_everything, &data);
	mlx_hook(data.test_window, 2, 1L<<0, &events, &data);
	mlx_hook(data.test_window, 3, 1L<<1, &events, &data);
	
	mlx_hook(data.window, 17, 0, destroy_everything, &data);
	// mlx_hook(data.window, 2, 1L<<0, &events, &data);
	// mlx_hook(data.window, 3, 1L<<1, &events, &data);
	mlx_loop(data.mlx);
	//parsing();
	//execution();
}
