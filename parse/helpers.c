/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:28:08 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/11/18 19:28:08 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '\n')
			return (1);
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*skip_whitespace(char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (line && line[i] && ft_isspace(line[i]))
		i++;
	tmp = ft_strdup(line + i);
	free(line);
	return (tmp);
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
