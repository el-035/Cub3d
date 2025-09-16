#include "cub3d.h"

int is_wall(t_mlx *mlx, double x, double y)
{
	double xx;
	double yy;
	double angle;
	double rad;

	angle = 0;
	rad = 0.04;
	while (angle < (2 * M_PI))
	{
		xx = x + (cos(angle) * rad);
		yy = y + (sin(angle) * rad);
		angle += (M_PI / 4);
		if (mlx->input->input_map[(int)yy][(int)xx] == '1')
			return (1);
	}
	return 0;
}

int up_down(int key, t_mlx *mlx)
{
	if (key == UP)
	{
		if (is_wall(mlx, (mlx->game->pos_x + mlx->game->dir_x * MOVEMENT), (mlx->game->pos_y + mlx->game->dir_y * MOVEMENT)) == 1)
			return 0;
		draw_back(mlx); //DEL	//DEL
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT); //DEL //DEL
		mlx->game->pos_x += mlx->game->dir_x * MOVEMENT; //or 0,15??
    	mlx->game->pos_y += mlx->game->dir_y * MOVEMENT;
		save_screen_buffer(mlx, mlx->game->ray);
		calculate_rays(mlx); //DEL
	}
	if (key == DOWN)
	{
		if (is_wall(mlx, (mlx->game->pos_x - mlx->game->dir_x * MOVEMENT), (mlx->game->pos_y - mlx->game->dir_y * MOVEMENT)) == 1)
			return 0;
		draw_back(mlx); //DEL
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT); //DEL
		mlx->game->pos_x -= mlx->game->dir_x * MOVEMENT;
		mlx->game->pos_y -= mlx->game->dir_y * MOVEMENT;
		save_screen_buffer(mlx, mlx->game->ray);
		calculate_rays(mlx); //DEL
	}
	return (0);
}

int left_right(int key, t_mlx *mlx)
{
	if (key == LEFT)
	{
		if (is_wall(mlx, (mlx->game->pos_x - (-mlx->game->dir_y) * MOVEMENT), (mlx->game->pos_y - mlx->game->dir_x * MOVEMENT)) == 1)
			return 0;
		draw_back(mlx); //DEL
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT); //DEL
		mlx->game->pos_x -= (-mlx->game->dir_y) * MOVEMENT;
		mlx->game->pos_y -= mlx->game->dir_x * MOVEMENT;
		save_screen_buffer(mlx, mlx->game->ray);
		calculate_rays(mlx); //DEL
	}
	if (key == RIGHT)
	{
		if (is_wall(mlx, (mlx->game->pos_x + (-mlx->game->dir_y) * MOVEMENT), (mlx->game->pos_y + mlx->game->dir_x * MOVEMENT)) == 1)
			return 0;
		draw_back(mlx); //DEL
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT); //DEL
		mlx->game->pos_x += (-mlx->game->dir_y) * MOVEMENT;
		mlx->game->pos_y += mlx->game->dir_x * MOVEMENT;
		save_screen_buffer(mlx, mlx->game->ray);
		calculate_rays(mlx); //DEL
	}
	return (0);
}

int rotate(int key, t_mlx *mlx)
{
	if (key == ROT_LEFT)
	{
		mlx->game->angle -= ROTATION;
		draw_back(mlx); //DEL
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT); //DEL
		mlx->game->dir_x = cos(mlx->game->angle);
		mlx->game->dir_y = sin(mlx->game->angle);
		save_screen_buffer(mlx, mlx->game->ray);
		calculate_rays(mlx); //DEL
	}
	if (key == ROT_RIGHT)
	{
		mlx->game->angle += ROTATION;
		draw_back(mlx); //DEL
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT); //DEL
		mlx->game->dir_x = cos(mlx->game->angle);
		mlx->game->dir_y = sin(mlx->game->angle);
		save_screen_buffer(mlx, mlx->game->ray);
		calculate_rays(mlx); //DEL
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
