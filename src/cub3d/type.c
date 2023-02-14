/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 21:15:05 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/11 21:15:06 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	valid_line(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\n')
		return (0);
	while (line[i])
	{
		if (line[i] == '\n')
			break ;
		if (line[i] != '0' && line[i] != '1' && line[i] != 'W' \
			&& line[i] != 'N' && line[i] != 'E' && line[i] != 'S'
			&& line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	type_color(char *line)
{
	int		i;
	long	num;
	int		ret;
	char	**tmp;

	if (get_sizec(line, ',') != 2)
		print_error("color error");
	while (*line == ' ')
		line++;
	tmp = ft_split(line, ',');
	if (!tmp)
		print_error("allocated error");
	i = -1;
	ret = 0;
	while (++i < 3)
	{
		ret = ret << 8;
		num = ft_myatoi(tmp[i]);
		if (num < 0 || num > 255)
			print_error("invalid value of color");
		ret += (int)num;
	}
	free_str(tmp);
	return (ret);
}

int	get_type(char *line)
{
	while ((9 <= *line && *line <= 13) || *line == 32)
		line++;
	if (*line == 'N' && *(line + 1) == 'O' && *(line + 2) == ' ')
		return (0);
	else if (*line == 'W' && *(line + 1) == 'E' && *(line + 2) == ' ')
		return (1);
	else if (*line == 'S' && *(line + 1) == 'O' && *(line + 2) == ' ')
		return (2);
	else if (*line == 'E' && *(line + 1) == 'A' && *(line + 2) == ' ')
		return (3);
	else if (*line == 'F' && *(line + 1) == ' ')
		return (4);
	else if (*line == 'C' && *(line + 1) == ' ')
		return (5);
	else if (valid_line(line))
		return (6);
	return (-1);
}
