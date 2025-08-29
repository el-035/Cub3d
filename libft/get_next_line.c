/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:57:04 by codespace         #+#    #+#             */
/*   Updated: 2025/08/29 17:37:43 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_freejoin(char *dest, char *buf, int *flag)
{
	char *temp;
	temp = ft_strjoin(dest, buf);
	if (!temp)
	{
		free(buf);
		buf = NULL;
		*flag = 1;
		return (NULL);
	}
	free(dest);
	dest = NULL;
	return (temp);
}

char	*ft_free(char *dest, char *buf)
{
	if (dest)
		free(dest);
	if (buf)
		free(buf);
	dest = NULL;
	buf = NULL;
	return (NULL);
}

char	*ft_remainder(char *dest)
{
	char	*rem;
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (dest[i] && dest[i] != '\n')
		i++;
	if (dest[i] == '\0')
		return (ft_free(dest, NULL));
	i++;
	rem = malloc(ft_strlen(dest) - i + 1);
	if (!rem)
		return (ft_free(dest, NULL));
	while (dest[i])
		rem[n++] = dest[i++];
	rem[n] = '\0';
	ft_free(dest, NULL);
	return (rem);
}

char	*create_line(char *dest)
{
	int		i;
	char	*temp;

	i = 0;
	while (dest[i] && dest[i] != '\n')
		i++;
	temp = malloc(i + 2);
	if (!temp)
		return (ft_free(dest, NULL));
	i = 0;
	while (dest[i] && dest[i] != '\n')
	{
		temp[i] = dest[i];
		i++;
	}
	if (dest[i] == '\n')
		temp[i++] = '\n';
	temp[i] = '\0';
	return (temp);
}

char	*read_lines(int fd, char *dest, char *buf, int *flag)
{
	int		check;

	check = 1;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (ft_free(dest, NULL));
	while (1)
	{
		check = read(fd, buf, BUFFER_SIZE);
		if (check < 0)
		{
			*flag = 1;
			return (ft_free(dest, buf));
		}
		buf[check] = '\0';
		if (check == 0)
		{
			if (*dest == '\0' || !dest)
				return (ft_free(dest, buf));
			break ;
		}
		dest = ft_freejoin(dest, buf, flag);
		if (!dest || ft_strchr(buf, '\n') || (check < BUFFER_SIZE && *dest))
			break ;
	}
	free(buf);
	return (dest);
}

char	*get_next_line(int fd, int *flag)
{
	static char	*dest;
	char		*ret_line;
	char		*buf;

	buf = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (dest)
			free(dest);
		dest = NULL;
		*flag = 1;
		return (NULL);
	}
	if (!dest)
	{
		dest = ft_strdup("");
		if (!dest)
			return (NULL);
	}
	dest = read_lines(fd, dest, buf, flag);
	if (!dest)
		return (NULL);
	ret_line = create_line(dest);
	if (!ret_line)
		return (ft_free(dest, NULL));
	dest = ft_remainder(dest);
	return (ret_line);
}

/* #include <stdio.h>

int	main(void)
{
	int fd;
	char *next_line;

	fd = open("file.txt", O_RDONLY);
	if (fd < 0)
		return (0);
	while (1)
	{
		next_line = get_next_line(fd);
		if (!next_line)
			break ;
		ft_printf("%s", next_line);
		free(next_line);
	}
	close(fd);
} */