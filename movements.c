#include "cub3d.h"

int is_wall(t_mlx *mlx, double x, double y)
{
	printf("map [%f][%f]\n", y, x/* , mlx->input->input_map[y][x] */);
	double xx;
	double yy;
	double angle = 0;
	double rad = 0.06;
	if (mlx->input->input_map[(int)y][(int)x] == '1')
		return (1);

	while (angle < (2 * M_PI))
	{
		//printf("rad %f\n", rad);

		xx = x + (cos(angle) * rad);
		yy = y + (sin(angle) * rad);
		angle += (M_PI / 4);
		printf("map [%f][%f]\n", yy, xx/* , mlx->input->input_map[y][x] */);

		printf("map [%d][%d] = %c\n", (int)yy, (int)xx, mlx->input->input_map[(int)yy][(int)xx]);

		if (mlx->input->input_map[(int)yy][(int)xx] == '1')
			return (1);
	}




	/* //("posx: %d	posy: %d\n", x, y);
	//printf("x %d, y %d\n", x, y);
	if (mlx->input->input_map[(int)y][(int)x] == '1')
		return (1); */
	return 0;
}

int up_down(int key, t_mlx *mlx)
{
	if (key == UP)
	{
		//printf("posx: %f	posy: %f\n", mlx->game->pos_x, mlx->game->pos_y);
		if (is_wall(mlx, (mlx->game->pos_x + mlx->game->dir_x * MOVEMENT), (mlx->game->pos_y + mlx->game->dir_y * MOVEMENT)) == 1)
			return 0;
		draw_back(mlx);
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);
		mlx->game->pos_x += mlx->game->dir_x * MOVEMENT; //or 0,15??
    	mlx->game->pos_y += mlx->game->dir_y * MOVEMENT;
		save_screen_buffer(mlx, mlx->game->ray);
		calculate_rays(mlx);
		calculate_rays(mlx);
	}
	if (key == DOWN)
	{
		//printf("posx: %f	posy: %f\n", mlx->game->pos_x, mlx->game->pos_y);
		if (is_wall(mlx, (mlx->game->pos_x - mlx->game->dir_x * MOVEMENT), (mlx->game->pos_y - mlx->game->dir_y * MOVEMENT)) == 1)
			return 0;
		draw_back(mlx);
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);
		mlx->game->pos_x -= mlx->game->dir_x * MOVEMENT;
		mlx->game->pos_y -= mlx->game->dir_y * MOVEMENT;
		save_screen_buffer(mlx, mlx->game->ray);
		calculate_rays(mlx);
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
		save_screen_buffer(mlx, mlx->game->ray);
		calculate_rays(mlx);
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
		save_screen_buffer(mlx, mlx->game->ray);
		calculate_rays(mlx);
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
		save_screen_buffer(mlx, mlx->game->ray);
		calculate_rays(mlx);
		calculate_rays(mlx);
	}
	if (key == ROT_RIGHT)
	{
		mlx->game->angle += ROTATION;
		draw_back(mlx);
		draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);
		mlx->game->dir_x = cos(mlx->game->angle);
		mlx->game->dir_y = sin(mlx->game->angle);
		save_screen_buffer(mlx, mlx->game->ray);
		calculate_rays(mlx);
		calculate_rays(mlx);
	}
	return (0);
}

int events(int key, t_mlx *mlx)
{
	if (key == ESC)
		destroy_everything(mlx);
	//printf("\n");
	
	if (key == ROT_LEFT || key == ROT_RIGHT)
		rotate(key, mlx);
	if (key == UP || key == DOWN)
		up_down(key, mlx);
	if (key == LEFT || key == RIGHT)
		left_right(key, mlx);
	return 0;
}
