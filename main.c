/*  FUNCTIONS ALLOWED
• open, close, read, write, printf, malloc, free, perror, strerror, exit, gettimeofday.
• All functions of the math library (-lm man man 3 math).
• gettimeofday()
• All functions of the MinilibX library. */

#include "cub3d.h"

double calculate_dir(t_game *game, t_input *input, double dir_x, double dir_y)
{
	printf("ray dir x %f, ray dir y %f\n", dir_x, dir_y);
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

	printf("stepx %d, stepy%d\n", game->ray->step_x, game->ray->step_y);

	game->ray->delta_dist_x = fabs(1 / dir_x);
	game->ray->delta_dist_y = fabs(1 / dir_y);
	printf("deltax %f, deltay%f\n", game->ray->delta_dist_x, game->ray->delta_dist_y);

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
	printf("distx %f, disty%f\n", game->ray->dist_x, game->ray->dist_y);

	game->ray->side_dist_y = game->ray->delta_dist_y;
	game->ray->side_dist_x = game->ray->delta_dist_x;

	if (game->ray->dist_x != 0)	
		game->ray->side_dist_x = game->ray->dist_x * game->ray->delta_dist_x;
	if (game->ray->dist_y != 0)
		game->ray->side_dist_y = game->ray->dist_y * game->ray->delta_dist_y;

	printf("sidex %f, sidey%f\n", game->ray->side_dist_x, game->ray->side_dist_y);

	game->ray->y = (int)game->pos_y /* - game->ray->side_dist_y */;
	game->ray->x = (int)game->pos_x /* - game->ray->side_dist_x */;
	printf("x %d, y%d\n", game->ray->x, game->ray->y);
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
			printf("x smaller: sidex %f, sidey%f\n", game->ray->side_dist_x, game->ray->side_dist_y);
			printf("map [%d][%d] = %c\n", game->ray->y, game->ray->x, input->input_map[game->ray->y][game->ray->x]);
			if (input->input_map[game->ray->y][game->ray->x] == '1')
			{
				game->ray->distance = game->ray->side_dist_x;
				break;
			}
			game->ray->side_dist_x += game->ray->delta_dist_x;
		}
		else if (game->ray->side_dist_x > game->ray->side_dist_y)
		{
			game->ray->y += game->ray->step_y;
			
			printf("y smaller: sidex %f, sidey%f\n", game->ray->side_dist_x, game->ray->side_dist_y);
			printf("map [%d][%d] = %c\n", game->ray->y, game->ray->x, input->input_map[game->ray->y][game->ray->x]);
			if (input->input_map[game->ray->y][game->ray->x] == '1')
			{
				game->ray->distance = game->ray->side_dist_y;
				break;
			}
			game->ray->side_dist_y += game->ray->delta_dist_y;

		}
		if (!input->input_map[game->ray->y][game->ray->x])
			break;
	}	
	printf("direction: %f\n", game->ray->distance);
    return (game->ray->distance);
}


#define M_PI 3.14159265358979323846
#define FOV_HALF_RAD 0.57596


int calculate_rays(t_mlx *mlx)
{
	calculate_dir(mlx->game, mlx->input, mlx->game->dir_x, mlx->game->dir_y);
	draw_ray(mlx, mlx->game->ray, 0xFF0000, mlx->game->dir_x, mlx->game->dir_y);

	double rad = FOV_HALF_RAD;

	int i = 1;
	while (i < 20)
	{
		rad = -FOV_HALF_RAD + i * ((2 * FOV_HALF_RAD) / (20 - 1));
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
	draw_grid(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);

	mlx->game->pos_x = 5.0;
	mlx->game->pos_y = 4.0;
	mlx->game->dir_x = 0;
	mlx->game->dir_y = -1;
	calculate_rays(mlx);
	return (0);
}

int events(int key, t_mlx *mlx)
{
	if (key == ESC)
		destroy_everything(mlx);
	if (key == LEFT)
	{
		draw_back(mlx);
		draw_grid(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		calculate_dir(mlx->game, mlx->input, mlx->game->ray->ray_dir_x, mlx->game->ray->ray_dir_y);
		draw_ray(mlx, mlx->game->ray, 0x000FF, mlx->game->ray->ray_dir_x, mlx->game->ray->ray_dir_y);
	}


	return 0;
}


int main (void)
{
	t_mlx		data;
	t_input		*input;
	int			width;
	int			heignt;
	data.mlx = mlx_init();
	if (!data.mlx)
		return 1; //errors("Allocation failed", data);
	data.game = malloc(sizeof(t_game));
	data.game->ray = malloc(sizeof(t_ray));
	input = create_hardcoded_map();
	input->n_texture = mlx_xpm_file_to_image(data.mlx, "test_images/purple_N.png", &width, &heignt); //protect
	data.input = input;
	data.window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	data.test_window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "2d test");
	test_start(&data);
	mlx_hook(data.test_window, 17, 0, destroy_everything, &data);
	mlx_key_hook(data.test_window, &events, &data);
	mlx_hook(data.window, 17, 0, destroy_everything, &data);
	mlx_key_hook(data.window, &events, &data);
	mlx_loop(data.mlx);
	//parsing();
	//execution();
}
