#include "../cub3d.h"

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int empty_line(char *line)
{
    int i = 0;
    while (line[i])
    {
        if (!ft_isspace(line[i]))
            return (0);
        i++;
    }
    return (1);
}

char	*skip_whitespace(char *line)
{
	while (line && *line && ft_isspace(*line))
		line++;
	return (line);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i] && map[i][0])
	{
		printf("[%s]\n", map[i]);
		i++;
	}
}

int	find_start(char *s)
{
	int	i;

	i = 0;
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
