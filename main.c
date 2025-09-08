/*  FUNCTIONS ALLOWED
• open, close, read, write, printf, malloc, free, perror, strerror, exit, gettimeofday.
• All functions of the math library (-lm man man 3 math).
• gettimeofday()
• All functions of the MinilibX library. */

#include "cub3d.h"

t_input *init_stuff(t_mlx *data)
{
	t_input		*input;

	data->mlx = mlx_init();
	if (!data->mlx)
		return NULL; //errors("Allocation failed", data);
	data->game = malloc(sizeof(t_game));	//protect
	data->game->ray = malloc(sizeof(t_ray));//protect
	input = create_hardcoded_map();	//delet

	//data->input = data->input;
	
	return input;
}

int test(t_mlx *data)
{
	data->input->n_texture->img = mlx_xpm_file_to_image(data->mlx, "test_images/beer.xpm", &data->input->n_texture->width, &data->input->n_texture->height); //delete
	//protect

	mlx_put_image_to_window(data->mlx, data->window, data->input->n_texture->img, 0, 0);
	data->input->n_texture->data = mlx_get_data_addr(data->input->n_texture->img, &data->input->n_texture->bits_per_pixel, &data->input->n_texture->size_line, &data->input->n_texture->endian);
	printf("culo\n");
	return 0;
}


int main (void)
{
	t_mlx		data;

	data.input = init_stuff(&data);
	
	//parsing();
	data.window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	data.test_window = mlx_new_window(data.mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT, "2d test");	//delete
	test(&data);
	test_start(&data); //delete
	mlx_hook(data.test_window, 17, 0, destroy_everything, &data);
	mlx_hook(data.test_window, 2, 1L<<0, &events, &data);
	mlx_hook(data.test_window, 3, 1L<<1, &events, &data);
	
	mlx_hook(data.window, 17, 0, destroy_everything, &data);
	// mlx_hook(data.window, 2, 1L<<0, &events, &data);
	// mlx_hook(data.window, 3, 1L<<1, &events, &data);
	mlx_loop(data.mlx);
	//execution();
}
