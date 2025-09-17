#include "cub3d.h"

int	destroy_everything(t_mlx *data)
{
	if (data->input->n_texture->img)
		mlx_destroy_image(data->mlx, data->input->n_texture->img);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	/* if (data->test_window)		//DELETE!!
		mlx_destroy_window(data->mlx, data->test_window); */
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		//free(data->mlx);
	}
/* 	if (data->map)
		free_map(data->map); */
	exit (0);
}

/* int errors(char *msg, t_mlx *data)
{

} */