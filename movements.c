#include "cub3d.h"

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
		draw_back(mlx);
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);
		mlx->game->pos_x += mlx->game->dir_x * 0.15;
    	mlx->game->pos_y += mlx->game->dir_y * 0.15;
		calculate_rays(mlx);
	}
	if (key == S)
	{
		draw_back(mlx);
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);
		mlx->game->pos_x -= mlx->game->dir_x * 0.15;
    	mlx->game->pos_y -= mlx->game->dir_y * 0.15;
		calculate_rays(mlx);
	}
	if (key == A)
	{
		draw_back(mlx);
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);
		mlx->game->pos_x -=  (-mlx->game->dir_y) * 0.15;
		mlx->game->pos_y -= mlx->game->dir_x * 0.15;
		calculate_rays(mlx);
	}
	if (key == D)
	{
		draw_back(mlx);
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);
		mlx->game->pos_x += (-mlx->game->dir_y) * 0.15;
		mlx->game->pos_y += mlx->game->dir_x * 0.15;
		calculate_rays(mlx);
	}
	return 0;
}