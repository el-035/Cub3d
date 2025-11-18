#include "cub3d.h"

void init_stuff(t_mlx *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (parse_error(data, ERR_ALLOC, 1));
	data->game = malloc(sizeof(t_game));
	if (!data->game)
		return (parse_error(data, ERR_ALLOC, 1));

	data->game->ray = malloc(sizeof(t_ray));
	if (!data->game->ray)
		return (parse_error(data, ERR_ALLOC, 1));

	data->screen_data = malloc(sizeof(t_texture));
	if (!data->screen_data)
		return (parse_error(data, ERR_ALLOC, 1));
	memset(data->screen_data, 0, sizeof(t_texture));
}

int save_img(t_mlx *data)
{
	//protect???
	data->input->n_texture->img = mlx_xpm_file_to_image(data->mlx, data->input->n_texture->file_name, &data->input->n_texture->width, &data->input->n_texture->height); //delete
	data->input->n_texture->data = mlx_get_data_addr(data->input->n_texture->img, &data->input->n_texture->bits_per_pixel, &data->input->n_texture->size_line, &data->input->n_texture->endian);

	data->input->s_texture->img = mlx_xpm_file_to_image(data->mlx, data->input->s_texture->file_name, &data->input->s_texture->width, &data->input->s_texture->height); //delete
	data->input->s_texture->data = mlx_get_data_addr(data->input->s_texture->img, &data->input->s_texture->bits_per_pixel, &data->input->s_texture->size_line, &data->input->s_texture->endian);

	data->input->e_texture->img = mlx_xpm_file_to_image(data->mlx, data->input->e_texture->file_name, &data->input->e_texture->width, &data->input->e_texture->height); //delete
	data->input->e_texture->data = mlx_get_data_addr(data->input->e_texture->img, &data->input->e_texture->bits_per_pixel, &data->input->e_texture->size_line, &data->input->e_texture->endian);

	data->input->w_texture->img = mlx_xpm_file_to_image(data->mlx, data->input->w_texture->file_name, &data->input->w_texture->width, &data->input->w_texture->height); //delete
	data->input->w_texture->data = mlx_get_data_addr(data->input->w_texture->img, &data->input->w_texture->bits_per_pixel, &data->input->w_texture->size_line, &data->input->w_texture->endian);

	//protect
	data->screen_data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->screen_data->data = mlx_get_data_addr(data->screen_data->img, &data->screen_data->bits_per_pixel, &data->screen_data->size_line, &data->screen_data->endian);
	return 0;
}

void init_game(t_mlx *mlx)
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
