/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 21:14:45 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/11 21:15:00 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*ft_mystrdup(char *line)
{
	int		len;
	char	*ret;
	int		i;
	int		nl;

	nl = 0;
	if (ft_strchr(line, '\n'))
		nl = 1;
	i = 0;
	while ((line[i] && (9 <= line[i] && line[i] <= 13)) || line[i] == 32)
		i++;
	len = 0;
	while (line[i + len])
		len++;
	ret = (char *)malloc(sizeof(char) * (len - nl + 1));
	if (!ret)
		print_error("allocated error");
	ft_strlcpy(ret, line + i, len);
	return (ret);
}

long	ft_myatoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	if (ft_strlen(str) > 11)
		return (-1);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	if (*str && *str != '\n' && !ft_isdigit(*str))
		return (-1);
	return (sign * result);
}
