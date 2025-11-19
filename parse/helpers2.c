#include "../cub3d.h"

int	is_validchar(char c)
{
	return (c == '\r' || c == ' ' || c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

int	is_direction(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	add_line(t_mlx *data, char *next_line, int fd, int i)
{
	data->input->file[i] = ft_strdup(next_line);
	if (!data->input->file[i])
		(free(next_line), close(fd), parse_error(data, ERR_ALLOC, 1));
	return (1);
}
