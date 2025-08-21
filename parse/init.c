#include "../cub3d.h"

void	init(t_mlx *data, int file_lines)
{
	data->input = malloc(sizeof(t_input));
	if (!data->input)
		parse_error(data, ERR_ALLOC);
    data->input->file = ft_calloc(file_lines + 1, sizeof(char *));
    if (!data->input->file)
		parse_error(data, ERR_ALLOC);
	data->input->map = NULL;
	data->input->map = NULL;
	data->input->n_texture = NULL;
	data->input->s_texture = NULL;
	data->input->e_texture = NULL;
	data->input->w_texture = NULL;
	data->mlx = NULL;
	data->window = NULL;
	data->input->line_length = 0;
	data->input->line_count = 0;
    data->input->info_count = 0;
}

int     find_start(char *s)
{
    int i = 0;
    while (s && s[i] && ft_isspace(s[i]))
        i++;
    while (s[i] && !ft_isspace(s[i]) && s[i] != '\n')
        i++;
    if (s[i] && s[i] == '\n')
        return (-1);
    while (s && s[i] && ft_isspace(s[i]))
        i++;
    return (i);
}

int     find_len(char *s)
{
    int i = 0;
    while (s[i] && !ft_isspace(s[i]) && s[i] != '\n')
        i++;
    return (i);
}

char    *middle_substr(t_mlx *data, char *s, int start, int len)
{
    char *txt = ft_calloc(len + 1, sizeof(char));
    if (!txt)
        parse_error(data, ERR_ALLOC);
    ft_strlcpy(txt, s + start, len + 1);
    return (txt);
}

int rgb_to_hex(char *txt)
{
    int r;
    int g;
    int b;
    char **rgb_arr = ft_split(txt, ',');
    r = ft_atoi(rgb_arr[0]);
    g = ft_atoi(rgb_arr[1]);
    b = ft_atoi(rgb_arr[2]);
    int rgb = (convert_dec_hex(r, 'X') * 100 + convert_dec_hex(g, 'X')) * 100 + convert_dec_hex(b, 'X');
    // printf("\nRGB: #%i\n", rgb);
    (void)rgb;
    return 0;
}

char    *extract_filename(t_mlx *data, char *line)
{
    int start = find_start(line);
    if (start < 0)
        return (NULL);
    int len = find_len(line+start);
    return (middle_substr(data, line, start, len));
}

void process_line(t_mlx *data, t_input *input, char *line, int type)
{
    char *extract;
    extract = extract_filename(data, line);
    if (!extract)
    {
        if (type < 5)
            parse_error(data, ERR_NO_TEX);
        parse_error(data, ERR_NO_COL);
    }
    if (type == 1)
        input->n_texture = extract;
    else if (type == 2)
        input->s_texture = extract;
    else if (type == 3)
        input->e_texture = extract;
    else if (type == 4)
        input->w_texture = extract;
    else if (type == 5)
        input->f_color = rgb_to_hex(extract);
    else if (type == 6)
        input->c_color = rgb_to_hex(extract);
}

// set colors to hex
// fill struct
void	fill_struct(t_mlx *data)
{
    (void)data;
}