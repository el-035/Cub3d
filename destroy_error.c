#include "cub3d.h"

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
	{
		mlx_destroy_display(data->mlx);
		//free(data->mlx);
	}

	if (data->screen_data)
		free(data->screen_data);
	
	if (data->game->ray)
		free(data->game->ray);
	if (data->game)
		free(data->game);
	free(data->mlx);
	free_exit(data, 0);
/* 	if (data->map)
		free_map(data->map); */
	exit (0);
}

/* int errors(char *msg, t_mlx *data)
{

} */