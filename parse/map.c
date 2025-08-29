#include "../cub3d.h"

void	check_map_dimensions(t_mlx *data, t_input *input, char **arr)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	// if (!ft_strncmp("\n", line, 1)) // need new empty line check, right now empty lines are not in arr
	//     (free(line), parse_error(data, ERR_MAP_LINE));
	while (arr && arr[a])
	{
		b = 0;
		while (arr && arr[a] && arr[a][b] && arr[a][b] != '\n' && arr[a][b] != '\r')
			b++;
		if (b > input->line_length)
			input->line_length = b;
		a++;
	}
	input->line_count = a;
	(void)data;
}

void	fill_map(t_input *input, char **arr)
{
	int	b;
	int	a;

	a = 0;
	while (arr && arr[a])
	{
		// len = ft_strlen(arr[a]);
		// if (len > 0 && arr[a][len - 1] == '\n')
		// 	len--;
		// ft_strlcpy(input->map[a], arr[a], len + 1);
		b = 0;
		while (arr && arr[a] && arr[a][b] && arr[a][b] != '\n' && arr[a][b] != '\r')
		{
			input->map[a][b] = arr[a][b];
			b++;
		}
		while (b < input->line_length)
		{
			input->map[a][b] = ' ';
			b++;
		}
		input->map[a][b] = 0;
		a++;
	}
}

void	alloc_map(t_mlx *data)
{
	int	i;

	i = 0;
	data->input->map = calloc(data->input->line_count + 1, sizeof(char *));
	if (!data->input->map)
		parse_error(data, ERR_ALLOC, 1);
	while (i < data->input->line_count)
	{
		data->input->map[i] = calloc(data->input->line_length + 1,
				sizeof(char));
		if (!data->input->map[i])
			parse_error(data, ERR_ALLOC, 1);
		i++;
	}
}
