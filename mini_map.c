#include "cub3d.h"

int tile_color(t_input *input, int x, int y)
{
	if (input->map[y][x] == '0')
		return (WHITE);
/* 	else if (input->map[y][x] == '1')
		return (BLACK); */
	else if (input->map[y][x] == 'S' || input->map[y][x] == 'N' || input->map[y][x] == 'E' || input->map[y][x] == 'W')
		return (WHITE);
	else
		return (NO_CLR);
}

void put_tile(t_texture *map, int color, int x, int y)
{
	int x_tile;
	int y_tile;
	int pos;

	if (color == NO_CLR)
		return ;
	y_tile = TILE_SIZE;
	y *= TILE_SIZE;
	x *= TILE_SIZE;
	while (y_tile-- > 0)
	{
		x_tile = TILE_SIZE;
		while(x_tile-- > 0)
		{
			pos = ((y_tile + y) * map->size_line) + (x_tile + x) * (map->bits_per_pixel / 8);
			*(int *)(map->data + pos) = color;
		}
	}	
}

void map_buffer(t_mlx *data, t_input *input/* , t_ray *ray */)
{
	int x;
	int y;

	y = 0;
	while (y < input->line_count)
	{
		x = 0;
		while(x < input->line_length)
		{
			put_tile(data->screen_data, tile_color(input, x, y), x, y);
			x++;
		}
		y++;
	}
}

/* void draw_ray(t_mlx *data, t_ray *ray)
{
	int start_x = data->game->pos_x * TILE_SIZE;
	int start_y = data->game->pos_y * TILE_SIZE;
	int end_x = (data->game->pos_x + ray->ray_dir_x * ray->distance) * TILE_SIZE;
	int end_y = (data->game->pos_y + ray->ray_dir_y * ray->distance) * TILE_SIZE;

	double dx = end_x - start_x;
    double dy = end_y - start_y;
    double steps = fmax(fabs(dx), fabs(dy));
    double step_x = dx / steps;
    double step_y = dy / steps;

    double x = start_x;
    double y = start_y;

    for (int i = 0; i <= (int)steps; i++)
    {
        mlx_pixel_put(data->mlx, data->window, (int)x, (int)y, BLUE);
        x += step_x;
        y += step_y;
    }
} */

void put_rays(t_mlx *data, t_ray *ray)
{
	int i = 0;
	int offset;

	while(i < N_RAYS)
	{
		offset = -HALF_FOV + i * ((2*HALF_FOV) / (N_RAYS - 1));
		ray->ray_dir_x = data->game->dir_x * cos(offset) - data->game->dir_y * sin(offset);
		ray->ray_dir_y = data->game->dir_x * sin(offset) + data->game->dir_y * cos(offset);
		calculate_dir(data->game, data->input);
		//draw actual ray on 2d map
		draw_ray(data, ray);
		i++;
	}
}
