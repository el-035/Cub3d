#include "../cub3d.h"

int	find_filename_len(char *s)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (s[i] && !ft_isspace(s[i]) && s[i] != '\n')
		i++;
	while (s[i + a] && ft_isspace(s[i + a]) && s[i + a] != '\n')
		a++;
	if (s[i + a] && !ft_isspace(s[i + a]) && s[i + a] != '\n')
		return (-1);
	return (i);
}

char	*middle_substr(t_mlx *data, char *s, int start, int len)
{
	char	*txt;

	txt = ft_calloc(len + 1, sizeof(char));
	if (!txt)
		parse_error(data, ERR_ALLOC);
	ft_strlcpy(txt, s + start, len + 1);
	return (txt);
}

char	*extract_filename(t_mlx *data, char *line)
{
	int	start;
	int	len;

	start = find_start(line);
	if (start < 0)
		parse_error(data, ERR_NO_TEX);
	len = find_filename_len(line + start);
	if (len < 0)
		parse_error(data, ERR_INV_TEX);
	return (middle_substr(data, line, start, len));
}

void	parse_texture(t_mlx *data, t_input *input, char *line, int type)
{
	char    *extract;

	extract = extract_filename(data, line);
	if (type == 1)
		input->n_texture = extract;
	else if (type == 2)
		input->s_texture = extract;
	else if (type == 3)
		input->e_texture = extract;
	else if (type == 4)
		input->w_texture = extract;
}
