#include "cub3d.h"


void	parse_error(t_mlx *data, char *msg, int free_check)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	if (free_check)
		free_exit(data, 1);
	exit(1);
}

void	free_arr(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return ;
	// while (arr && arr[i])
	// 	i++;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_exit(t_mlx *data, int errnum)
{
	if (!data->input)
		exit(errnum);
	if (data->input->file && data->input->file[0])
		free_arr(data->input->file); // invalid free sometimes
	if (data->input->map)
		free_arr(data->input->map);
	if (data->input->map_cpy)
		free_arr(data->input->map_cpy);
	if (data->input->n_texture->file_name)
		free(data->input->n_texture->file_name);
	if (data->input->s_texture->file_name)
		free(data->input->s_texture->file_name);
	if (data->input->e_texture->file_name)
		free(data->input->e_texture->file_name);
	if (data->input->w_texture->file_name)
		free(data->input->w_texture->file_name);
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