#include "cub3d.h"

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
		while (y < ray->wall_start)
		{
			pos = y++ * data->screen_data->size_line + x * (data->screen_data->bits_per_pixel / 8);
			*(int *)(data->screen_data->data + pos) = data->input->c_color;
		}
		while (y < ray->wall_end && y < WINDOW_HEIGHT)
			put_wall(data, ray, y++, x);
		while (y < WINDOW_HEIGHT)
		{
			pos = y++ * data->screen_data->size_line + x * (data->screen_data->bits_per_pixel / 8);
			*(int *)(data->screen_data->data + pos) = data->input->f_color;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->screen_data->img, 0, 0);
}
