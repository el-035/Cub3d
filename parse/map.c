#include "../cub3d.h"

void check_map_dimensions(t_mlx *data, t_input *input, char **arr)
{
    int a = 0;
    int b = 0;
    // if (!ft_strncmp("\n", line, 1)) // need new empty line check, right now empty lines are not in arr
    //     (free(line), parse_error(data, ERR_MAP_LINE));
    while (arr && arr[a])
    {
        b = 0;
        while (arr && arr[a] && arr[a][b])
            b++;
        if (b > input->line_length)
            input->line_length = b;
        a++;
    }
    input->line_count = a;
    (void)data;
}

void    fill_map(t_input *input, char **arr)
{
    int len;
    int i = 0;
    while (arr && arr[i])
    {
        len = ft_strlen(arr[i]);
        if (len > 0 && arr[i][len-1] == '\n')
            len--;
        ft_strlcpy(input->map[i], arr[i], len + 1);
        i++;
    }
}

void    alloc_map(t_mlx *data)
{
    int i = 0;
    data->input->map = calloc(data->input->line_count + 1, sizeof(char *));
    if (!data->input->map)
        parse_error(data, ERR_ALLOC);
    while (i < data->input->line_count)
    {
        data->input->map[i] = calloc(data->input->line_length + 1, sizeof(char));
        if (!data->input->map[i])
            parse_error(data, ERR_ALLOC);
        i++;
    }
}