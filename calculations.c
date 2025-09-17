#include "cub3d.h"

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
	dist_calc(game);
	while (game->ray->y >= 0 && game->ray->y < input->line_count && game->ray->x >= 0 && game->ray->x < input->line_length)
	{
		if (input->map[game->ray->y][game->ray->x] == '1')
			break ;
		if (game->ray->side_dist_x <= game->ray->side_dist_y)
		{
			if (side_dist_x(game, input) == 1)
				break;
		}
		else if (game->ray->side_dist_x > game->ray->side_dist_y)
		{
			if (side_dist_y(game, input) == 1)
				break;
		}
		if (!input->map[game->ray->y][game->ray->x])
			break;
	}	
	game->ray->distance = game->ray->distance / (game->ray->ray_dir_x * game->dir_x + game->ray->ray_dir_y * game->dir_y);
}

t_texture	*find_dir(t_mlx *data, t_game *game, t_ray *ray, int x)
{
	t_texture *wall;

	game->plane_x = -game->dir_y * tan(HALF_FOV);
	game->plane_y = game->dir_x * tan(HALF_FOV);
	memset(ray, 0, sizeof(t_ray));
	ray->camera = 2.0 * (double)x / (double)WINDOW_WIDTH - 1;
	ray->ray_dir_x = game->dir_x + game->plane_x * ray->camera;
	ray->ray_dir_y = game->dir_y + game->plane_y * ray->camera;
	calculate_dir(game, data->input);
	wall = wall_side(data, ray);
	return (wall);
}


