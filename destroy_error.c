#include "cub3d.h"

int	destroy_everything(t_mlx *data)
{
	/* if (data->shroom_image)
		mlx_destroy_image(data->mlx, data->shroom_image); */
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		//free(data->mlx);
	}
/* 	if (data->input->map)
		free_map(data->input->map); */
	exit (0);
}

/* int errors(char *msg, t_mlx *data)
{

} */