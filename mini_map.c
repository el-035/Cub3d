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

void put_rays(t_mlx *data, t_ray *ray)
{
	
}
