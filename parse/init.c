#include "../cub3d.h"

void	init(t_mlx *data, int nb_lines)
{
	data->input = NULL;
	data->input = malloc(sizeof(t_input));
	if (!data->input)
		parse_error(data, ERR_ALLOC, 0);
	data->input->file = NULL;
	data->input->map = NULL;
	data->input->map_cpy = NULL;
	data->input->n_texture = NULL;
	data->input->e_texture = NULL;
	data->input->s_texture = NULL;
	data->input->w_texture = NULL;
	(void)nb_lines;
	data->input->file = ft_calloc(nb_lines + 1, sizeof(char *));
	if (!data->input->file)
		parse_error(data, ERR_ALLOC, 1);

	//textures 
	data->input->n_texture = malloc(sizeof(t_texture));
	if (!data->input->n_texture)
		return;	//malloc error
	memset(data->input->n_texture, 0, sizeof(t_texture));
	data->input->n_texture->file_name = NULL;

	data->input->s_texture = malloc(sizeof(t_texture));
	if (!data->input->s_texture)
		return;	//malloc error
	memset(data->input->s_texture, 0, sizeof(t_texture));
	data->input->s_texture->file_name = NULL;

	data->input->w_texture = malloc(sizeof(t_texture));
	if (!data->input->w_texture)
		return;	//malloc error
	memset(data->input->w_texture, 0, sizeof(t_texture));
	data->input->w_texture->file_name = NULL;

	data->input->e_texture = malloc(sizeof(t_texture));
	if (!data->input->e_texture)
		return;	//malloc error
	memset(data->input->e_texture, 0, sizeof(t_texture));
	data->input->e_texture->file_name = NULL;

	/* data->input->s_texture->file_name = NULL;
	data->input->e_texture->file_name = NULL;
	data->input->w_texture->file_name = NULL; */
	data->mlx = NULL;
	data->window = NULL;
	data->input->line_length = 0;
	data->input->info_count = 0;
    data->input->line_count = 0;

}
