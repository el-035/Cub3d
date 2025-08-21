#include "../cub3d.h"

int     ft_isspace(int c)
 {
    return ((c >= 9 && c <= 13) || c == ' ');
 }

char *skip_whitespace(char *line)
{
    while (line && *line && ft_isspace(*line))
        line++;
    return (line);
}

void    print_map(char **map)
{
    int i = 0;
    while (map && map[i] && map[i][0])
    {
        printf("%s\n", map[i]);
        i++;
    }
}



// void    check_map()
// {
//     int		fd;
// 	int		len;
// 	int		max_len;
// 	int		read_check;
// 	char	c;

//     fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 		parse_error(data, ERR_PERM);
// 	len = 0;
// 	max_len = 0;
// 	while (1)
// 	{
// 		read_check = read(fd, &c, 1);
// 		if (read_check < 0)
// 			(close(fd), parse_error(data, ERR_READ));
// 		else if (read_check == 0)
// 			break ;
// 		len++;
// 		if (c == '\n')
// 		{
// 			data->input->line_count++;
// 			if (len > max_len)
// 				max_len = len;
// 			len = 0;
// 		}
// 	}
//     close(fd);
// 	data->input->line_length = max_len;
// }