/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 17:11:51 by majosue           #+#    #+#             */
/*   Updated: 2020/01/04 11:59:55 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_wrdnbr(char const *s, char c)
{
	int n;

	n = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			n++;
		while (*s != c && *s != '\0')
			s++;
	}
	return (n);
}

int	ft_append(char **param, char **line)
{
	char *tmp;

	if (!*param)
	{
		if (!(*param = ft_strjoin(*line, " ")))
			return (0);
		free(*line);
		line = 0;
		return (1);
	}
	tmp = *line;
	if (!(*line = ft_strjoin(*line, " ")))
		return (0);
	free(tmp);
	tmp = *param;
	if (!(*param = ft_strjoin(*param, *line)))
		return (0);
	free(tmp);
	free(*line);
	*line = 0;
	return (1);
}

void	cleanup(char **param, char **line)
{
	if (*param)
	{
		free(*param);
		(*param) = 0;
	}
	if (*line)
	{
		free(*line);
		(*line) = 0;
	}
}

char		**ft_readmap(int fd, int *width, int *height)
{
	char *param;
	char *line;
	char *error;
	char **array;
	
	error = "";
	line = 0;
	*height = 0;
	*width = 0;
	param = 0;
	array = 0;
	while (get_next_line(fd, &line) > 0 && !(*error))
	{
		*width = *width == 0 ? ft_wrdnbr(line, ' ') : *width;
		error = *width != ft_wrdnbr(line, ' ') ?\
		"Found wrong line length. Exiting." : error;
		error = !ft_append(&param, &line) ? "Unexpected error. Exiting" : error;
		(*height)++;
	}
	error = *width == 0 ? "No data found." : error;
	array = ft_strsplit(param, ' ');
	if (*error || !array)
		*error ? ft_putendl(error) : ft_putendl("Unexpected error. Exiting");
	cleanup(&param, &line);
	return (array);

}
