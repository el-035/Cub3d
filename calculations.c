#include "cub3d.h"

void	wall_calc(t_ray *ray)
{
	ray->wall_height = ( WINDOW_HEIGHT) / ray->corr_dis;
	ray->wall_start = (WINDOW_HEIGHT - ray->wall_height) / 2;
	//printf("wall atart %d\n", ray->wall_start);

	if (ray->wall_start < 0)
	{

		ray->img_start = (abs(ray->wall_start)) * TILE_SIZE / ray->wall_height;
		//printf("img start %d\n", ray->img_start);
		ray->wall_height += ray->wall_start;
		ray->wall_start = 0;
	}
	else
		ray->img_start = 0;
	ray->wall_end = (WINDOW_HEIGHT + ray->wall_height) / 2;
	if (ray->wall_end >= WINDOW_HEIGHT)
	{
		ray->wall_end = WINDOW_HEIGHT -1;
	}
	/* printf("Distance: %f, Wall height: %d, Start: %d, img start %d\n", 
		ray->corr_dis, ray->wall_height, ray->wall_start, ray->img_start);
	printf("End: %d, Final start=%d, end=%d, img end %d\n\n\n", 
		ray->wall_end, ray->wall_start, ray->wall_end, ray->img_end); */
}

double calculate_dir(t_game *game, t_input *input, double dir_x, double dir_y) // that should actually be ray dir directly
{
	//should i memset ray struct every time here? probably yes
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
				if (/* game->ray-> */dir_x < 0)
					game->ray->wall = W;
				else
					game->ray->wall = E;
				game->ray->pixel_pos = (game->pos_y + dir_y * game->ray->distance);
				game->ray->pixel_pos -= floor(game->ray->pixel_pos);
				game->ray->pixel = (int)(game->ray->pixel_pos *TILE_SIZE);
				//printf("%d pixel_pos  y  %d\n", game->ray->wall, game->ray->pixel);
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
				if (/* game->ray->ray_ */dir_y < 0)
  					game->ray->wall = N;
				else
					game->ray->wall = S;
				game->ray->distance = game->ray->side_dist_y;
				game->ray->pixel_pos = (game->pos_x + dir_x * game->ray->distance);

				game->ray->pixel_pos -= floor(game->ray->pixel_pos);
				game->ray->pixel = (int)(game->ray->pixel_pos *TILE_SIZE);
				//printf("%d pixel_pos x %d\n", game->ray->wall, game->ray->pixel);

				break;
			}
			game->ray->side_dist_y += game->ray->delta_dist_y;

		}
		if (!input->input_map[game->ray->y][game->ray->x])
			break;
	}	
//	printf("direction: %f\n", game->ray->distance);
	game->ray->corr_dis = game->ray->distance / (dir_x * game->dir_x + dir_y * game->dir_y);
	//printf("%f\n\n", game->ray->corr_dis);

	//CALCULATE WALL HEIGHT
	wall_calc(game->ray);
	return (game->ray->distance);
}


int calculate_rays(t_mlx *mlx)
{
	calculate_dir(mlx->game, mlx->input, mlx->game->dir_x, mlx->game->dir_y);
	draw_ray(mlx, mlx->game->ray, 0xFF0000, mlx->game->dir_x, mlx->game->dir_y);
	

	double rad = HALF_FOV;

	int i = 1;
	while (i < 80)
	{
		rad = -HALF_FOV + i * ((2 * HALF_FOV) / (80 - 1));
/* 		mlx->game->ray->ray_dir_x = mlx->game->dir_x * cos(rad) - mlx->game->dir_y * sin(rad);
		mlx->game->ray->ray_dir_y = mlx->game->dir_x * sin(rad) + mlx->game->dir_y * cos(rad); */
		calculate_dir(mlx->game, mlx->input, mlx->game->dir_x * cos(rad) - mlx->game->dir_y * sin(rad), mlx->game->dir_x * sin(rad) + mlx->game->dir_y * cos(rad));
		draw_ray(mlx, mlx->game->ray, 0x000FF, mlx->game->dir_x * cos(rad) - mlx->game->dir_y * sin(rad), mlx->game->dir_x * sin(rad) + mlx->game->dir_y * cos(rad));
		i++;
	}
	rad = -HALF_FOV;

/* 	mlx->game->ray->ray_dir_x = mlx->game->dir_x * cos(rad) - mlx->game->dir_y * sin(rad);
	mlx->game->ray->ray_dir_y = mlx->game->dir_x * sin(rad) + mlx->game->dir_y * cos(rad); */
	/* calculate_dir(mlx->game, mlx->input, mlx->game->dir_x * cos(rad) - mlx->game->dir_y * sin(rad), mlx->game->dir_x * sin(rad) + mlx->game->dir_y * cos(rad));
	draw_ray(mlx, mlx->game->ray, 0xFF0000, mlx->game->dir_x * cos(rad) - mlx->game->dir_y * sin(rad), mlx->game->dir_x * sin(rad) + mlx->game->dir_y * cos(rad)); */
	

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

	/* 
	rad = HALF_FOV;

	mlx->game->ray->ray_dir_x = mlx->game->dir_x * cos(rad) - mlx->game->dir_y * sin(rad);
	mlx->game->ray->ray_dir_y = mlx->game->dir_x * sin(rad) + mlx->game->dir_y * cos(rad);
	calculate_dir(mlx->game, mlx->input, mlx->game->ray->ray_dir_x, mlx->game->ray->ray_dir_y);
	draw_ray(mlx, mlx->game->ray, 0xFF0000, mlx->game->ray->ray_dir_x, mlx->game->ray->ray_dir_y); */
	return (0);
}

int test_start(t_mlx *mlx)
{
	draw_2d_map_simple(mlx);
	draw_back(mlx);
	draw_grid(mlx, T_WINDOW_WIDTH, T_WINDOW_HEIGHT);

	mlx->game->pos_x = 3.0;
	mlx->game->pos_y = 4.0;
	mlx->game->dir_x = 0;
	mlx->game->dir_y = -1;
	mlx->game->angle = atan2(mlx->game->dir_y, mlx->game->dir_x);
	//calculate_rays(mlx);
	return (0);
}
