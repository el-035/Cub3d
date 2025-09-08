#include "cub3d.h"

int is_wall(t_mlx *mlx, int x, int y)
{
	//("map [%d][%d] = %c\n", y, x, mlx->input->input_map[y][x]);
	//("posx: %d	posy: %d\n", x, y);
	
	if (mlx->input->input_map[y][x] == '1')
		return (1);
	return 0;
}

int up_down(int key, t_mlx *mlx)
{
	if (key == UP)
	{
		//("posx: %f	posy: %f\n", mlx->game->pos_x, mlx->game->pos_y);
		if (is_wall(mlx, (mlx->game->pos_x + mlx->game->dir_x * 0.1), (mlx->game->pos_y + mlx->game->dir_y * 0.1)) == 1)
			return 0;
		draw_back(mlx);
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);
		mlx->game->pos_x += mlx->game->dir_x * MOVEMENT; //or 0,15??
    	mlx->game->pos_y += mlx->game->dir_y * MOVEMENT;
		calculate_rays(mlx);
	}
	if (key == DOWN)
	{
		//("posx: %f	posy: %f\n", mlx->game->pos_x, mlx->game->pos_y);
		if (is_wall(mlx, (mlx->game->pos_x - mlx->game->dir_x * 0.1), (mlx->game->pos_y - mlx->game->dir_y * 0.1)) == 1)
			return 0;
		draw_back(mlx);
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);
		mlx->game->pos_x -= mlx->game->dir_x * MOVEMENT;
		mlx->game->pos_y -= mlx->game->dir_y * MOVEMENT;
		calculate_rays(mlx);
	}
	return (0);
}

int left_right(int key, t_mlx *mlx)
{
	if (key == LEFT)
	{
		//("posx: %f	posy: %f\n", mlx->game->pos_x, mlx->game->pos_y);
		if (is_wall(mlx, (mlx->game->pos_x - (-mlx->game->dir_y) * MOVEMENT), (mlx->game->pos_y - mlx->game->dir_x * MOVEMENT)) == 1)
			return 0;
		draw_back(mlx);
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);
		mlx->game->pos_x -= (-mlx->game->dir_y) * MOVEMENT;
		mlx->game->pos_y -= mlx->game->dir_x * MOVEMENT;
		calculate_rays(mlx);
	}
	if (key == RIGHT)
	{
		//("posx: %f	posy: %f\n", mlx->game->pos_x, mlx->game->pos_y);
		if (is_wall(mlx, (mlx->game->pos_x + (-mlx->game->dir_y) * MOVEMENT), (mlx->game->pos_y + mlx->game->dir_x * MOVEMENT)) == 1)
			return 0;
		draw_back(mlx);
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);
		mlx->game->pos_x += (-mlx->game->dir_y) * MOVEMENT;
		mlx->game->pos_y += mlx->game->dir_x * MOVEMENT;
		calculate_rays(mlx);
	}
	return (0);
}

int rotate(int key, t_mlx *mlx)
{
	if (key == ROT_LEFT)
	{
		mlx->game->angle -= ROTATION;
		draw_back(mlx);
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);
		mlx->game->dir_x = cos(mlx->game->angle);
		mlx->game->dir_y = sin(mlx->game->angle);
		calculate_rays(mlx);
	}
	if (key == ROT_RIGHT)
	{
		mlx->game->angle += ROTATION;
		draw_back(mlx);
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);
		mlx->game->dir_x = cos(mlx->game->angle);
		mlx->game->dir_y = sin(mlx->game->angle);
		calculate_rays(mlx);
	}
	return (0);
}

int events(int key, t_mlx *mlx)
{
	if (key == ESC)
		destroy_everything(mlx);
	if (key == ROT_LEFT || key == ROT_RIGHT)
		rotate(key, mlx);
	if (key == UP || key == DOWN)
		up_down(key, mlx);
	if (key == LEFT || key == RIGHT)
		left_right(key, mlx);
	return 0;
}
