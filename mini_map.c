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

void draw_char(t_mlx *data, t_game *game)
{
	int x = game->pos_x * TILE_SIZE - 1;
	int y = game->pos_y * TILE_SIZE - 1;
	int i = 0;
	while (i < 3)
	{
		int j = 0;
		y = game->pos_y * TILE_SIZE - 1;
		while (j < 3)
		{
			x = game->pos_x * TILE_SIZE - 1;
			mlx_pixel_put(data->mlx, data->window, x, y, RED);
			j++;
			y++;
		}
		i++;
		x++;
	}
}

/* void draw_ray(t_mlx *data, t_ray *ray)
{
	double start[2] = {data->game->pos_x * TILE_SIZE, data->game->pos_y * TILE_SIZE};
	double end[2] = {start[0] + ray->ray_dir_x * (ray->distance * TILE_SIZE), start[1] + ray->ray_dir_y * (ray->distance * TILE_SIZE)};
	double delta[2] = {end[0] - start[0], end[1] - start[1]};
	double steps;
	if (fabs(delta[0]) > fabs(delta[1]))
		steps = fabs(delta[0]);
	else
		steps = fabs(delta[1]);
	double inc[2] = {delta[0] / steps, delta[1] / steps};
	
	int i = 0;
	while(i <= steps)
	{
		mlx_pixel_put(data->mlx, data->window, (int)(start[0]), (int)(start[1]), BLUE);
		start[0] += inc[0];
		start[1] += inc[1];
		i++;
	}
}

void put_rays(t_mlx *data, t_ray *ray)
{
	int i = 0;
	int offset;
	
	while(i < N_RAYS)
	{
		offset = -HALF_FOV + (2*HALF_FOV) /(i*  (N_RAYS - 1));
		ray->ray_dir_x = data->game->dir_x * cos(offset) - data->game->dir_y * sin(offset);
		ray->ray_dir_y = data->game->dir_x * sin(offset) + data->game->dir_y * cos(offset);
		calculate_dir(data->game, data->input);
		draw_ray(data, ray);
		i++;
	}

} */
