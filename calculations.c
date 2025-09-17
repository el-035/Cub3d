#include "cub3d.h"

void	wall_calc(t_ray *ray)
{
	ray->wall_height = ( WINDOW_HEIGHT) / ray->distance;
	ray->wall_start = (WINDOW_HEIGHT - ray->wall_height) / 2;

	if (ray->wall_start < 0)
	{
		ray->img_start = (abs(ray->wall_start)) * TILE_SIZE / ray->wall_height;
		ray->wall_height += ray->wall_start;
		ray->wall_start = 0;
	}
	else
		ray->img_start = 0;
	ray->wall_end = (WINDOW_HEIGHT + ray->wall_height) / 2;
	if (ray->wall_end >= WINDOW_HEIGHT)
		ray->wall_end = WINDOW_HEIGHT -1;

}

void dist_calc(t_game *game)
{
	double	dist_x;
	double	dist_y;

	dist_x = 0;
	dist_y = 0;
	game->ray->delta_dist_x = fabs(1 / game->ray->ray_dir_x);
	game->ray->delta_dist_y = fabs(1 / game->ray->ray_dir_y);

	if (game->ray->ray_dir_y < 0)
		dist_y = game->pos_y - (int)floor(game->pos_y);
	if (game->ray->ray_dir_y > 0)
		dist_y = (int)ceil(game->pos_y) - game->pos_y;
	if (game->ray->ray_dir_x < 0)
		dist_x = game->pos_x - (int)floor(game->pos_x);
	if (game->ray->ray_dir_x > 0)
		dist_x = (int)ceil(game->pos_x) - game->pos_x;

	game->ray->side_dist_y = game->ray->delta_dist_y;
	game->ray->side_dist_x = game->ray->delta_dist_x;

	if (dist_x != 0)	
		game->ray->side_dist_x = dist_x * game->ray->delta_dist_x;
	if (dist_y != 0)
		game->ray->side_dist_y = dist_y * game->ray->delta_dist_y;
}

void init_step_pos(t_game *game)
{
	//CALCULATE STEP (in which direction it takes a step)
	if (game->ray->ray_dir_y < 0)
		game->ray->step_y = -1;
	else if (game->ray->ray_dir_y > 0)
		game->ray->step_y = 1;
	if (game->ray->ray_dir_x < 0)
		game->ray->step_x = -1;
	else if (game->ray->ray_dir_x > 0)
		game->ray->step_x = 1;

	//CALCULATE START POS IN THE GRID
	game->ray->y = (int)game->pos_y;
	game->ray->x = (int)game->pos_x;

	if (game->pos_y == (int)game->pos_y && game->ray->ray_dir_y < 0)
		game->ray->y -= 1;
	if (game->pos_x == (int)game->pos_x && game->ray->ray_dir_x < 0)
		game->ray->x -= 1;
}

void calculate_dir(t_game *game, t_input *input)
{
	init_step_pos(game);

	//CALCULATE side delta and dist
	dist_calc(game);

	while (game->ray->y >= 0 && game->ray->y < input->line_count && game->ray->x >= 0 && game->ray->x < input->line_length)
	{
		if (input->map[game->ray->y][game->ray->x] == '1')
			break ;
		if (game->ray->side_dist_x <= game->ray->side_dist_y)
		{
			game->ray->x += game->ray->step_x;
			
			if (input->map[game->ray->y][game->ray->x] == '1')
			{
				game->ray->distance = game->ray->side_dist_x;
				if (game->ray->ray_dir_x < 0)
					game->ray->wall = W;
				else
					game->ray->wall = E;
				break;
			}
			game->ray->side_dist_x += game->ray->delta_dist_x;
		}
		else if (game->ray->side_dist_x > game->ray->side_dist_y)
		{
			game->ray->y += game->ray->step_y;
			
			if (input->map[game->ray->y][game->ray->x] == '1')
			{
				if (game->ray->ray_dir_y < 0)
  					game->ray->wall = N;
				else
					game->ray->wall = S;
				game->ray->distance = game->ray->side_dist_y;
				break;
			}
			game->ray->side_dist_y += game->ray->delta_dist_y;
		}
		if (!input->map[game->ray->y][game->ray->x])
			break;
	}	
	game->ray->distance = game->ray->distance / (game->ray->ray_dir_x * game->dir_x + game->ray->ray_dir_y * game->dir_y);
	//CALCULATE WALL HEIGHT
	wall_calc(game->ray);
}


void find_dir(t_mlx *data, t_game *game, t_ray *ray, int x)
{
	game->plane_x = -game->dir_y * tan(HALF_FOV);
	game->plane_y = game->dir_x * tan(HALF_FOV);
	/* printf("Player dir: (%f, %f)\n", game->dir_x, game->dir_y);
	printf("Plane: (%f, %f)\n", game->plane_x, game->plane_y); */
	memset(ray, 0, sizeof(t_ray));

	ray->camera = 2.0 * (double)x / (double)WINDOW_WIDTH - 1;
	//printf("camera %f\nx %d\n", ray->camera, x);
	ray->ray_dir_x = game->dir_x + game->plane_x * ray->camera;
	ray->ray_dir_y = game->dir_y + game->plane_y * ray->camera;
	
	calculate_dir(game, data->input/* , ray->ray_dir_x, ray->ray_dir_y */);
}


