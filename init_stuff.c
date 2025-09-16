#include "cub3d.h"

t_input *init_stuff(t_mlx *data)
{
	t_input		*input;

	data->mlx = mlx_init();
	if (!data->mlx)
		return NULL; //errors("Allocation failed", data);
	data->game = malloc(sizeof(t_game));	//protect
	if (!data->game)
		return (NULL);	//malloc error

	data->game->ray = malloc(sizeof(t_ray));//protect
	if (!data->game->ray)
		return (NULL);	//malloc error

	data->screen_data = malloc(sizeof(t_texture));
	if (!data->screen_data)
		return (NULL);	//malloc error
	memset(data->screen_data, 0, sizeof(t_texture));
		
	//so far still in the hardcoded map:

/* 	data->input->n_texture = malloc(sizeof(t_texture));
	if (!data->input->n_texture)
		return (NULL);	//malloc error
	memset(input->n_texture, 0, sizeof(t_texture));

	data->input->s_texture = malloc(sizeof(t_texture));
	if (!data->input->s_texture)
		return (NULL);	//malloc error
	memset(input->s_texture, 0, sizeof(t_texture));

	data->input->w_texture = malloc(sizeof(t_texture));
	if (!data->input->w_texture)
		return (NULL);	//malloc error
	memset(input->w_texture, 0, sizeof(t_texture));
	
	data->input->e_texture = malloc(sizeof(t_texture));
	if (!data->input->e_texture)
		return (NULL);	//malloc error
	memset(input->e_texture, 0, sizeof(t_texture)); */
	
	//data->input = data->input;
	input = create_hardcoded_map();	//delet
	
	return input;
}

int save_img(t_mlx *data)
{
	//allocation for the structs is with the hardcoded map
	data->input->n_texture->img = mlx_xpm_file_to_image(data->mlx, data->input->n_texture->file_name, &data->input->n_texture->width, &data->input->n_texture->height); //delete
	data->input->n_texture->data = mlx_get_data_addr(data->input->n_texture->img, &data->input->n_texture->bits_per_pixel, &data->input->n_texture->size_line, &data->input->n_texture->endian);

	data->input->s_texture->img = mlx_xpm_file_to_image(data->mlx, data->input->s_texture->file_name, &data->input->s_texture->width, &data->input->s_texture->height); //delete
	data->input->s_texture->data = mlx_get_data_addr(data->input->s_texture->img, &data->input->s_texture->bits_per_pixel, &data->input->s_texture->size_line, &data->input->n_texture->endian);

	data->input->e_texture->img = mlx_xpm_file_to_image(data->mlx, data->input->e_texture->file_name, &data->input->e_texture->width, &data->input->e_texture->height); //delete
	data->input->e_texture->data = mlx_get_data_addr(data->input->e_texture->img, &data->input->e_texture->bits_per_pixel, &data->input->e_texture->size_line, &data->input->n_texture->endian);

	data->input->w_texture->img = mlx_xpm_file_to_image(data->mlx, data->input->w_texture->file_name, &data->input->w_texture->width, &data->input->w_texture->height); //delete
	data->input->w_texture->data = mlx_get_data_addr(data->input->w_texture->img, &data->input->w_texture->bits_per_pixel, &data->input->w_texture->size_line, &data->input->n_texture->endian);
	
	
	//protect
	data->screen_data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->screen_data->data = mlx_get_data_addr(data->screen_data->img, &data->screen_data->bits_per_pixel, &data->screen_data->size_line, &data->screen_data->endian);
	//printf("height %d\n", data->input->n_texture->height);
	//mlx_put_image_to_window(data->mlx, data->window, data->input->n_texture->img, 0, 0);
	
	return 0;
}