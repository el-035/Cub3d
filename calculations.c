#include "cub3d.h"

double calculate_dir(t_game *game, t_input *input, double dir_x, double dir_y)
{
	//printf("ray dir x %f, ray dir y %f\n", dir_x, dir_y);
	game->ray->step_x = 0;
	game->ray->step_y = 0;

	if (dir_y < 0)
		game->ray->step_y = -1;
	else if (dir_y > 0)
		game->ray->step_y = 1;
	if (dir_x < 0)
		game->ray->step_x = -1;
	else if (dir_x > 0)
		game->ray->step_x = 1;

	//printf("stepx %d, stepy%d\n", game->ray->step_x, game->ray->step_y);

	game->ray->delta_dist_x = fabs(1 / dir_x);
	game->ray->delta_dist_y = fabs(1 / dir_y);
	//printf("deltax %f, deltay%f\n", game->ray->delta_dist_x, game->ray->delta_dist_y);

	game->ray->dist_y = 0;
	game->ray->dist_x = 0;

	if (dir_y < 0)
		game->ray->dist_y = game->pos_y - (int)floor(game->pos_y);
	if (dir_y > 0)
		game->ray->dist_y = (int)ceil(game->pos_y) - game->pos_y;
	if (dir_x < 0)
		game->ray->dist_x = game->pos_x - (int)floor(game->pos_x);
	if (dir_x > 0)
		game->ray->dist_x = (int)ceil(game->pos_x) - game->pos_x;
	//printf("distx %f, disty%f\n", game->ray->dist_x, game->ray->dist_y);

	game->ray->side_dist_y = game->ray->delta_dist_y;
	game->ray->side_dist_x = game->ray->delta_dist_x;

	if (game->ray->dist_x != 0)	
		game->ray->side_dist_x = game->ray->dist_x * game->ray->delta_dist_x;
	if (game->ray->dist_y != 0)
		game->ray->side_dist_y = game->ray->dist_y * game->ray->delta_dist_y;

	//printf("sidex %f, sidey%f\n", game->ray->side_dist_x, game->ray->side_dist_y);

	game->ray->y = (int)game->pos_y /* - game->ray->side_dist_y */;
	game->ray->x = (int)game->pos_x /* - game->ray->side_dist_x */;
	//printf("x %d, y%d\n", game->ray->x, game->ray->y);
	if (game->pos_y == (int)game->pos_y && dir_y < 0)
	    game->ray->y -= 1;
	if (game->pos_x == (int)game->pos_x && dir_x < 0)
	    game->ray->x -= 1;
	game->ray->distance = 0;
	while (game->ray->y >= 0 && game->ray->y < input->line_count && game->ray->x >= 0 && game->ray->x < input->line_length)
	{
		if (input->input_map[game->ray->y][game->ray->x] == '1')
			break ;
		if (game->ray->side_dist_x <= game->ray->side_dist_y)
		{
			game->ray->x += game->ray->step_x;
			//printf("x smaller: sidex %f, sidey%f\n", game->ray->side_dist_x, game->ray->side_dist_y);
			//printf("map [%d][%d] = %c\n", game->ray->y, game->ray->x, input->input_map[game->ray->y][game->ray->x]);
			if (input->input_map[game->ray->y][game->ray->x] == '1')
			{
				game->ray->distance = game->ray->side_dist_x;
				game->ray->wall = V_WALL;
				/* game->ray->pixel_x = (game->pos_x + dir_x * game->ray->distance) * T_TILE_SIZE;
				game->ray->pixel_y = (game->pos_y + dir_y * game->ray->distance) * T_TILE_SIZE; */
				break;
			}
			game->ray->side_dist_x += game->ray->delta_dist_x;
		}
		else if (game->ray->side_dist_x > game->ray->side_dist_y)
		{
			game->ray->y += game->ray->step_y;
			
			//printf("y smaller: sidex %f, sidey%f\n", game->ray->side_dist_x, game->ray->side_dist_y);
			//printf("map [%d][%d] = %c\n", game->ray->y, game->ray->x, input->input_map[game->ray->y][game->ray->x]);
			if (input->input_map[game->ray->y][game->ray->x] == '1')
			{
				game->ray->distance = game->ray->side_dist_y;
				game->ray->wall = H_WALL;
/* 				game->ray->pixel_x = (game->pos_x + dir_x * game->ray->distance) * T_TILE_SIZE;
				game->ray->pixel_y = (game->pos_y + dir_y * game->ray->distance) * T_TILE_SIZE; */
				break;
			}
			game->ray->side_dist_y += game->ray->delta_dist_y;

		}
		if (!input->input_map[game->ray->y][game->ray->x])
			break;
	}	
	//printf("direction: %f\n", game->ray->distance);
	game->ray->ray_angle = atan2(game->ray->ray_dir_y, game->ray->ray_dir_x);
	game->ray->corr_dis = game->ray->distance * cos(game->ray->ray_angle - game->angle);
    return (game->ray->distance);
}




int calculate_rays(t_mlx *mlx)
{
	calculate_dir(mlx->game, mlx->input, mlx->game->dir_x, mlx->game->dir_y);
	draw_ray(mlx, mlx->game->ray, 0xFF0000, mlx->game->dir_x, mlx->game->dir_y);
	

	double rad = FOV_HALF_RAD;

	int i = 1;
	while (i < 80)
	{
		rad = -FOV_HALF_RAD + i * ((2 * FOV_HALF_RAD) / (80 - 1));
		mlx->game->ray->ray_dir_x = mlx->game->dir_x * cos(rad) - mlx->game->dir_y * sin(rad);
		mlx->game->ray->ray_dir_y = mlx->game->dir_x * sin(rad) + mlx->game->dir_y * cos(rad);
		calculate_dir(mlx->game, mlx->input, mlx->game->ray->ray_dir_x, mlx->game->ray->ray_dir_y);
		draw_ray(mlx, mlx->game->ray, 0x000FF, mlx->game->ray->ray_dir_x, mlx->game->ray->ray_dir_y);
		
		i++;
	}
	rad = -FOV_HALF_RAD;

	mlx->game->ray->ray_dir_x = mlx->game->dir_x * cos(rad) - mlx->game->dir_y * sin(rad);
	mlx->game->ray->ray_dir_y = mlx->game->dir_x * sin(rad) + mlx->game->dir_y * cos(rad);
	calculate_dir(mlx->game, mlx->input, mlx->game->ray->ray_dir_x, mlx->game->ray->ray_dir_y);
	draw_ray(mlx, mlx->game->ray, 0xFF0000, mlx->game->ray->ray_dir_x, mlx->game->ray->ray_dir_y);
	

/* 	if (mlx->game->ray->wall == 0) // vertical wall
	{
		printf("y %d\n", mlx->game->ray->step_y);
		for (int i = 0; i <= T_TILE_SIZE; i++)
			mlx_pixel_put(mlx->mlx, mlx->test_window, (int)mlx->game->ray->pixel_x + (mlx->game->ray->step_x * i), (int)mlx->game->ray->pixel_y , 0xFF0000);
	}
	else if (mlx->game->ray->wall == 1) // horizontal wall
	{
		printf("x %d\n", mlx->game->ray->step_x);
		for (int i = 0; i <= T_TILE_SIZE; i++)
			mlx_pixel_put(mlx->mlx, mlx->test_window, (int)mlx->game->ray->pixel_x , (int)mlx->game->ray->pixel_y + (mlx->game->ray->step_y * i), 0xFF0000);
	} */

	
	rad = FOV_HALF_RAD;

	mlx->game->ray->ray_dir_x = mlx->game->dir_x * cos(rad) - mlx->game->dir_y * sin(rad);
	mlx->game->ray->ray_dir_y = mlx->game->dir_x * sin(rad) + mlx->game->dir_y * cos(rad);
	calculate_dir(mlx->game, mlx->input, mlx->game->ray->ray_dir_x, mlx->game->ray->ray_dir_y);
	draw_ray(mlx, mlx->game->ray, 0xFF0000, mlx->game->ray->ray_dir_x, mlx->game->ray->ray_dir_y);
	return (0);
}

int test_start(t_mlx *mlx)
{
	draw_2d_map_simple(mlx);
	draw_back(mlx);
	draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);
	
	mlx->game->pos_x = 5.0;
	mlx->game->pos_y = 4.0;
	mlx->game->dir_x = 0;
	mlx->game->dir_y = -1;
	mlx->game->angle = atan2(mlx->game->dir_y, mlx->game->dir_x);
	calculate_rays(mlx);
	return (0);
}
