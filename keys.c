#include "cub3d.h"
#include <stdio.h>
int key_press(int key, t_mlx *data)
{
	if (key == ESC)
		destroy_everything(data);
	if (key == ROT_LEFT)
		data->keys[K_ROT_LEFT] = 1;
	if (key == ROT_RIGHT)
		data->keys[K_ROT_RIGHT] = 1;
	if (key == UP)
		data->keys[K_UP] = 1;
	if (key == DOWN)
		data->keys[K_DOWN] = 1;
	if (key == LEFT)
		data->keys[K_LEFT] = 1;
	if (key == RIGHT)
		data->keys[K_RIGHT] = 1;
	if (key == M)
	{
		data->is_map = 1;
		put_img(data, data->game->ray);
	}
	if (key == Q)
	{
		data->is_map = 0;
		put_img(data, data->game->ray);
	}
	return 0;
}

int key_release(int key, t_mlx *data)
{
	if (key == ROT_LEFT)
		data->keys[K_ROT_LEFT] = 0;
	if (key == ROT_RIGHT)
		data->keys[K_ROT_RIGHT] = 0;
	if (key == UP)
		data->keys[K_UP] = 0;
	if (key == DOWN)
		data->keys[K_DOWN] = 0;
	if (key == LEFT)
		data->keys[K_LEFT] = 0;
	if (key == RIGHT)
		data->keys[K_RIGHT] = 0;
	return 0;
}

int	events(t_mlx *mlx)
{
	if (mlx->keys[K_ROT_LEFT] == 1)
		rotate(ROT_LEFT, mlx);
	if (mlx->keys[K_ROT_RIGHT] == 1)
		rotate(ROT_RIGHT, mlx);
	if (mlx->keys[K_UP] == 1)
		up_down(UP, mlx);
	if (mlx->keys[K_DOWN] == 1)
		up_down(DOWN, mlx);
	if (mlx->keys[K_LEFT] == 1)
		left_right(LEFT, mlx);
	if (mlx->keys[K_RIGHT] == 1)
		left_right(RIGHT, mlx);
	return (0);
}