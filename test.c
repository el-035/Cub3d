#include "cub3d.h"
// Function to print the 2D map array
void print_map(char **map, int line_count, int line_length)
{
    int i, j;
    
    if (!map)
    {
        printf("Map is NULL\n");
        return;
    }
    
    printf("Map (%dx%d):\n", line_length, line_count);
    for (i = 0; i < line_count; i++)
    {
        for (j = 0; j < line_length; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
t_input *create_hardcoded_map(void)
{
    t_input *input;
    int i;
    
    // Allocate memory for the input structure
    input = malloc(sizeof(t_input));
    
    // Simple rectangular hardcoded map
    char *map_lines[] = {
        "1111111111111",
        "1001111111111",
        "1000000000011",
        "1101000000001",
        "1010000001001",
		"1001001001001",
		"1000000000001",
        "1111111111111",
    };

	input->direction = 'N';

    input->line_count = 8;
    input->line_length = 14;
    
    // Allocate memory for input_map array
    input->input_map = malloc(sizeof(char *) * (input->line_count + 1));
    
    // Copy each line and allocate memory
    for (i = 0; i < input->line_count; i++)
    {
        input->input_map[i] = malloc(strlen(map_lines[i]) + 1);
        strcpy(input->input_map[i], map_lines[i]);
    }
    input->input_map[input->line_count] = NULL; // Null terminate the array
    
	input->n_texture = malloc(sizeof(t_texture));
    if (!input->n_texture)
        return (NULL);
    memset(input->n_texture, 0, sizeof(t_texture));
    input->n_texture->file_name = strdup("./test_images/beer.xpm");

	input->e_texture = malloc(sizeof(t_texture));
    if (!input->e_texture)
        return (NULL);
    memset(input->e_texture, 0, sizeof(t_texture));
    input->e_texture->file_name = strdup("./test_images/e_texture.xpm");

	input->w_texture = malloc(sizeof(t_texture));
    if (!input->w_texture)
        return (NULL);
    memset(input->w_texture, 0, sizeof(t_texture));
    input->w_texture->file_name = strdup("./test_images/w_texture.xpm");

	input->s_texture = malloc(sizeof(t_texture));
    if (!input->s_texture)
        return (NULL);
    memset(input->s_texture, 0, sizeof(t_texture));
    input->s_texture->file_name = strdup("./test_images/s_texture.xpm");

    // Set unused textures to NULL

    
    // Set colors (random hex values)
    input->f_color = 0x654321; // Floor color (brownish)
    input->c_color = 0x87CEEB; // Ceiling color (sky blue)
    
    // Set player position in the middle
    input->player_x = 5;
    input->player_y = 3;
    //print_map(input->input_map, input->line_count, input->line_length);
    return input;
}


// Main function to draw the 2D map (simplified version)
void draw_2d_map_simple(t_mlx *mlx)
{
    int tile_w, tile_h;
    
    // Load the tile image
    mlx->test_tile = mlx_xpm_file_to_image(mlx->mlx, "test_images/tile.xpm", &tile_w, &tile_h);
    if (!mlx->test_tile)
        printf("CULO") ;// handle error if needed

    // Loop through each row and column of the map
    for (int y = 0; y < mlx->input->line_count; y++)
    {
        for (int x = 0; x < mlx->input->line_length; x++)
        {
            // Only put the tile if the map has '1' at this position
            if (mlx->input->input_map[y][x] == '1')
            {
                mlx_put_image_to_window(mlx->mlx, mlx->test_window, mlx->test_tile,
                                        x * T_TILE_SIZE, y * T_TILE_SIZE);
            }
        }
    }
}

void draw_back(t_mlx *mlx)
{
    int tile_w, tile_h;
    
    // Load the tile image
    mlx->test_back = mlx_xpm_file_to_image(mlx->mlx, "test_images/back.xpm", &tile_w, &tile_h);
    if (!mlx->test_tile)
        printf("CULO") ;// handle error if needed

    // Loop through each row and column of the map
    for (int y = 0; y < mlx->input->line_count; y++)
    {
        for (int x = 0; x < mlx->input->line_length; x++)
        {
            // Only put the tile if the map has '1' at this position
            if (mlx->input->input_map[y][x] == '0')
            {
                mlx_put_image_to_window(mlx->mlx, mlx->test_window, mlx->test_back,
                                        x * T_TILE_SIZE, y * T_TILE_SIZE);
            }
        }
    }
}


void	draw_ray(t_mlx *mlx, t_ray *ray, int color, double dir_x, double dir_y)
{
	
	// Start point: player position in pixels
	double start_x = mlx->game->pos_x * T_TILE_SIZE;
	double start_y = mlx->game->pos_y * T_TILE_SIZE;

	// End point: extend in player direction by ray->distance * 24 pixels
	double end_x = start_x + dir_x * (ray->distance * T_TILE_SIZE);
	double end_y = start_y + dir_y * (ray->distance * T_TILE_SIZE);

	// Compute deltas
	double dx = end_x - start_x;
	double dy = end_y - start_y;

	// Determine number of steps based on the longest axis
	double steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

	// Compute incremental steps for each pixel
	double x_inc = dx / steps;
	double y_inc = dy / steps;

	// Draw the ray pixel by pixel
	double x = start_x;
	double y = start_y;
	for (int i = 0; i <= steps; i++)
	{
		mlx_pixel_put(mlx->mlx, mlx->test_window, (int)x, (int)y, color);
		x += x_inc;
		y += y_inc;
	}
}

void	draw_grid(t_mlx *mlx, int win_width, int win_height)
{
	int x, y;

	// vertical lines
	x = 0;
	while (x < win_width)
	{
		y = 0;
		while (y < win_height)
		{
			mlx_pixel_put(mlx->mlx, mlx->test_window, x, y, GRAY);
			y++;
		}
		x += T_TILE_SIZE;
	}

	// horizontal lines
	y = 0;
	while (y < win_height)
	{
		x = 0;
		while (x < win_width)
		{
			mlx_pixel_put(mlx->mlx, mlx->test_window, x, y, GRAY);
			x++;
		}
		y += T_TILE_SIZE;
	}
}