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

void find_dir(t_mlx *data, t_game *game, t_ray *ray, int x)
{
	game->plane_x = -game->dir_y * tan(HALF_FOV);
	game->plane_y = game->dir_x * tan(HALF_FOV);
	/* printf("Player dir: (%f, %f)\n", game->dir_x, game->dir_y);
	printf("Plane: (%f, %f)\n", game->plane_x, game->plane_y); */

	ray->camera = 2.0 * (double)x / (double)WINDOW_WIDTH - 1;
	//printf("camera %f\nx %d\n", ray->camera, x);
	ray->ray_dir_x = game->dir_x + game->plane_x * ray->camera;
	ray->ray_dir_y = game->dir_y + game->plane_y * ray->camera;
	calculate_dir(game, data->input, ray->ray_dir_x, ray->ray_dir_y);
}

void	put_wall(t_mlx *data, t_ray *ray, int y, int x)
{
	int pos = 0;
	int img_pos;
	int	text_y;
	int text_x;
	t_texture *wall;

	if (ray->wall == W)
		wall = data->input->w_texture;
	else if (ray->wall == E)
		wall = data->input->e_texture;
	else if (ray->wall == S)
		wall = data->input->s_texture;
	else
		wall = data->input->n_texture;
	pos = y * data->screen_data->size_line + x * (data->screen_data->bits_per_pixel / 8);
	text_y = ray->img_start + ((y - ray->wall_start) * (wall->height - ray->img_start)) / ray->wall_height;
	text_x = (int)(ray->pixel_pos * wall->height) % wall->height;
	if (text_y >= wall->size_line) 
		text_y = wall->size_line - 1;
	if (text_y < 0)
		text_y = 0;
	img_pos = text_y * wall->size_line + text_x * (wall->bits_per_pixel / 8);
	*(int *)(data->screen_data->data + pos) = *(int *)(wall->data + img_pos);
}

void save_screen_buffer(t_mlx *data, t_ray *ray)
{
	int y = 0;
	int x = 0;
 	int pos = 0;
	
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		find_dir(data, data->game, ray, x);
		//printf("%d\n", ray->wall_start);
		while (y < ray->wall_start)
		{

			pos = y * data->screen_data->size_line + x * (data->screen_data->bits_per_pixel / 8);
			*(int *)(data->screen_data->data + pos) = data->input->c_color;
			y++;
		}
		while (y < ray->wall_end && y < WINDOW_HEIGHT)
			put_wall(data, ray, y++, x);
		while (y < WINDOW_HEIGHT)
		{
			pos = y * data->screen_data->size_line + x * (data->screen_data->bits_per_pixel / 8);
			*(int *)(data->screen_data->data + pos) = data->input->f_color;
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->screen_data->img, 0, 0);
}

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
	mlx_hook(data.test_window, 17, 0, destroy_everything, &data);
	mlx_hook(data.test_window, 2, 1L<<0, &events, &data);
	mlx_hook(data.test_window, 3, 1L<<1, &events, &data);
	
	mlx_hook(data.window, 17, 0, destroy_everything, &data);
	mlx_hook(data.window, 2, 1L<<0, &events, &data);
	mlx_hook(data.window, 3, 1L<<1, &events, &data);
	mlx_loop(data.mlx);
	//execution();
}
