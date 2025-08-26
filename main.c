/*  FUNCTIONS ALLOWED
• open, close, read, write, printf, malloc, free, perror, strerror, exit, gettimeofday.
• All functions of the math library (-lm man man 3 math).
• gettimeofday()
• All functions of the MinilibX library. */

#include "cub3d.h"

double calculate_dir(t_game *game, t_input *input)
{
	int step_x = 0;
	int step_y = 0;

	if (game->dir_y < 0)
		step_y = -1;
	else if (game->dir_y > 0)
		step_y = 1;
	if (game->dir_x < 0)
		step_x = -1;
	else if (game->dir_x > 0)
		step_x = 1;

	printf("stepx %d, stepy%d\n", step_x, step_y);
	double delta_dist_x;
	double delta_dist_y;

	delta_dist_x = fabs(1 / game->dir_x);
	delta_dist_y = fabs(1 / game->dir_y);
	printf("deltax %f, deltay%f\n", delta_dist_x, delta_dist_y);

	double dist_y = 0;
	double dist_x = 0;
	
	if (game->dir_y < 0)
		dist_y = game->pos_y - (int)floor(game->pos_y);
	if (game->dir_y > 0)
		dist_y = (int)ceil(game->pos_y) - game->pos_y;
	if (game->dir_x < 0)
		dist_x = game->pos_x - (int)floor(game->pos_x);
	if (game->dir_x > 0)
		dist_x = (int)ceil(game->pos_x) - game->pos_x;
	printf("distx %f, disty%f\n", dist_x, dist_y);

	double side_dist_y = 0;
	double side_dist_x = 0;

	if (dist_x != 0)	
		side_dist_x = dist_x * delta_dist_x;
	if (dist_y != 0)
		side_dist_y = dist_y * delta_dist_y;

	printf("sidex %f, sidey%f\n", side_dist_x, side_dist_y);
	
	int y = (int)game->pos_y /* - side_dist_y */;
	int x = (int)game->pos_x /* - side_dist_x */;
	printf("x %d, y%d\n", x, y);
	
	double distance = 0;
	while (1)
	{
		if (side_dist_x <= side_dist_y)
		{
			x += step_x;
			side_dist_x += delta_dist_x;
			printf("x smaller: sidex %f, sidey%f\n", side_dist_x, side_dist_y);
			printf("map %c\n", input->input_map[y][x]);
			if (input->input_map[y][x] == '1')
			{
				distance = side_dist_x;
				break;
			}
		}
		else if (side_dist_x > side_dist_y)
		{
			y += step_y;
			side_dist_y += delta_dist_y;
			printf("y smaller: sidex %f, sidey%f\n", side_dist_x, side_dist_y);
			printf("map %c\n", input->input_map[y][x]);
			if (input->input_map[y][x] == '1')
			{
				distance = side_dist_y;
				break;
			}
		}
		if (!input->input_map[y][x])
			break;
	}	
	printf("direction: %f\n", distance);
	printf("culo\n");
    return (distance);
}

int test_start(t_mlx *mlx)
{
	double dir;
	mlx->game->pos_x = 4.5;
	mlx->game->pos_y = 3.5;
	mlx->game->dir_x = -0.7071;
	mlx->game->dir_y = -0.7071;

	dir = calculate_dir(mlx->game, mlx->input);
	printf("direction: %f\n", dir);
	return (0);
}

int events(int key, t_mlx *data)
{
	if (key == 65307) //ESC
		destroy_everything(data);
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

	input = create_hardcoded_map();
	input->n_texture = mlx_xpm_file_to_image(data.mlx, "test_images/purple_N.png", &width, &heignt); //protect
	data.input = input;
	data.window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	test_start(&data);
	mlx_hook(data.window, 17, 0, destroy_everything, &data);
	mlx_key_hook(data.window, &events, &data);
	mlx_loop(data.mlx);
	//parsing();
	//execution();
}
