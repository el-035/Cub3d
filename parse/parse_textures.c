/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:29:25 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/11/18 19:29:25 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		parse_error(data, ERR_ALLOC, 1);
	ft_strlcpy(txt, s + start, len + 1);
	return (txt);
}

char	*extract_filename(t_mlx *data, char *line)
{
	int	start;
	int	len;

	start = find_start(line);
	if (start < 0)
		parse_error(data, ERR_NO_TEX, 1);
	len = find_filename_len(line + start);
	if (len < 0)
		parse_error(data, ERR_INV_TEX, 1);
	return (middle_substr(data, line, start, len));
}

void	parse_texture(t_mlx *data, t_input *input, char *line, int type)
{
	char	*extract;

	extract = extract_filename(data, line);
	if (access(extract, F_OK) != 0)
	{
		free(extract);
		parse_error(data, ERR_INV_TEX, 1);
	}
	if (type == 1)
		input->n_texture->file_name = ft_strdup(extract);
	else if (type == 2)
		input->s_texture->file_name = ft_strdup(extract);
	else if (type == 3)
		input->e_texture->file_name = ft_strdup(extract);
	else if (type == 4)
		input->w_texture->file_name = ft_strdup(extract);
	free(extract);
}
