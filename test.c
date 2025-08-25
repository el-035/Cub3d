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
        "1111111111",
        "1000000001",
        "1000000001",
        "1000N00001",
        "1000000001",
        "1111111111",
    };

	input->direction = 'N';

    input->line_count = 6;
    input->line_length = 10;
    
    // Allocate memory for input_map array
    input->input_map = malloc(sizeof(char *) * (input->line_count + 1));
    
    // Copy each line and allocate memory
    for (i = 0; i < input->line_count; i++)
    {
        input->input_map[i] = malloc(strlen(map_lines[i]) + 1);
        strcpy(input->input_map[i], map_lines[i]);
    }
    input->input_map[input->line_count] = NULL; // Null terminate the array
    
    // Allocate memory for texture paths
    input->n_texture = malloc(strlen("./test_impages/purple_N.xpm") + 1);
    input->s_texture = malloc(strlen("./test_impages/purple_N.xpm") + 1);
    input->w_texture = malloc(strlen("./test_impages/purple_N.xpm") + 1);
    input->e_texture = malloc(strlen("./test_impages/purple_N.xpm") + 1);
    
    // Copy texture paths
    strcpy(input->n_texture, "./test_impages/purple_N.xpm");
    strcpy(input->s_texture, "./test_impages/purple_N.xpm");
    strcpy(input->w_texture, "./test_impages/purple_N.xpm");
    strcpy(input->e_texture, "./test_impages/purple_N.xpm");
    
    // Set colors (random hex values)
    input->f_color = 0x654321; // Floor color (brownish)
    input->c_color = 0x87CEEB; // Ceiling color (sky blue)
    
    // Set player position in the middle
    input->player_x = 5;
    input->player_y = 3;
    print_map(input->input_map, input->line_count, input->line_length);
    return input;
}

