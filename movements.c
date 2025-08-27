#include "cub3d.h"

int is_wall(t_mlx *mlx, int x, int y)
{
	//("map [%d][%d] = %c\n", y, x, mlx->input->input_map[y][x]);
	//("posx: %d	posy: %d\n", x, y);
	
	if (mlx->input->input_map[y][x] == '1')
		return (1);
	return 0;
}

int events(int key, t_mlx *mlx)
{
	if (key == ESC)
		destroy_everything(mlx);
	if (key == LEFT)
	{
		mlx->game->angle -= 0.1;
		draw_back(mlx);
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);
		mlx->game->dir_x = cos(mlx->game->angle);
		mlx->game->dir_y = sin(mlx->game->angle);
		calculate_rays(mlx);
	}
	if (key == RIGHT)
	{
		mlx->game->angle += 0.1;
		draw_back(mlx);
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);
		mlx->game->dir_x = cos(mlx->game->angle);
		mlx->game->dir_y = sin(mlx->game->angle);
		calculate_rays(mlx);
	}
	if (key == W)
	{
		//("posx: %f	posy: %f\n", mlx->game->pos_x, mlx->game->pos_y);
		if (is_wall(mlx, (mlx->game->pos_x + mlx->game->dir_x * 0.1), (mlx->game->pos_y + mlx->game->dir_y * 0.1)) == 1)
			return 0;
		draw_back(mlx);
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);
		mlx->game->pos_x += mlx->game->dir_x * 0.10; //or 0,15??
    	mlx->game->pos_y += mlx->game->dir_y * 0.10;
		calculate_rays(mlx);
	}
	if (key == S)
	{
		//("posx: %f	posy: %f\n", mlx->game->pos_x, mlx->game->pos_y);
		if (is_wall(mlx, (mlx->game->pos_x - mlx->game->dir_x * 0.1), (mlx->game->pos_y - mlx->game->dir_y * 0.1)) == 1)
			return 0;
		draw_back(mlx);
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);
		mlx->game->pos_x -= mlx->game->dir_x * 0.10;
		mlx->game->pos_y -= mlx->game->dir_y * 0.10;
		calculate_rays(mlx);
	}
	if (key == A)
	{
		//("posx: %f	posy: %f\n", mlx->game->pos_x, mlx->game->pos_y);
		if (is_wall(mlx, (mlx->game->pos_x - (-mlx->game->dir_y) * 0.10), (mlx->game->pos_y - mlx->game->dir_x * 0.10)) == 1)
			return 0;
		draw_back(mlx);
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);
		mlx->game->pos_x -= (-mlx->game->dir_y) * 0.10;
		mlx->game->pos_y -= mlx->game->dir_x * 0.10;
		calculate_rays(mlx);
	}
	if (key == D)
	{
		//("posx: %f	posy: %f\n", mlx->game->pos_x, mlx->game->pos_y);
		if (is_wall(mlx, (mlx->game->pos_x + (-mlx->game->dir_y) * 0.10), (mlx->game->pos_y + mlx->game->dir_x * 0.10)) == 1)
			return 0;
		draw_back(mlx);
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);
		mlx->game->pos_x += (-mlx->game->dir_y) * 0.10;
		mlx->game->pos_y += mlx->game->dir_x * 0.10;
		calculate_rays(mlx);
	}
	return 0;
}