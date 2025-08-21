#include "cub3d.h"

void parse_error(t_mlx *data, char *msg)
{
    ft_putendl_fd("Error", 2);
    ft_putendl_fd(msg, 2);
    free_exit(data, 1);
    exit(1);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
    i--;
	while (i >= 0)
	{
        // printf("line: %s\n", arr[i]);
		free(arr[i]);
		i--;
	}
	free(arr);
	arr = NULL;
}

void    free_exit(t_mlx *data, int errnum)
{
    if (!data || !data->input)
        exit(errnum);
    if (data->input->file)
        free_arr(data->input->file);
    if (data->input->map)
        free_arr(data->input->map);
    if (data->input->n_texture)
        free(data->input->n_texture);
    if (data->input->s_texture)
        free(data->input->s_texture);
    if (data->input->e_texture)
        free(data->input->e_texture);
    if (data->input->w_texture)
        free(data->input->w_texture);
    if (data->input)
        free(data->input);
    // destroy_everything(data); // add errnum to this function
}