/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 21:15:24 by eunrlee           #+#    #+#             */
/*   Updated: 2023/02/13 16:37:58 by wocheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	parse_line(t_game *game, char *line, int type)
{
	if (type == 6)
	{
		game->map->map_temp = ft_strjoin(game->map->map_temp, line);
		return ;
	}
	while ((9 <= *line && *line <= 13) || *line == 32)
		line++;
	if (type >= 0 && type <= 3)
	{
		if (game->text[type].path)
			print_error("Invalid number of texture");
		game->text[type].path = ft_mystrdup(line + 2);
	}
	else if (type == 4)
	{
		if (game->bgcolor->floor != -1)
			print_error("invalid number of floor color");
		game->bgcolor->floor = type_color(line + 1);
	}
	else if (type == 5)
	{
		if (game->bgcolor->ceiling != -1)
			print_error("invalid number of ceiling color");
		game->bgcolor->ceiling = type_color(line + 1);
	}
}

int	trans_map(t_game *game, char **temp, int cnt)
{
	int	x;
	int	y;

	y = -1;
	while (temp[++y])
	{
		game->map->map[y] = (int *)malloc(sizeof(int) * game->map->width);
		if (!game->map->map[y])
			print_perror("allocated error");
		ft_memset(game->map->map[y], -1, sizeof(int) * game->map->width);
		x = -1;
		while (temp[y][++x])
		{
			if (temp[y][x] == '0' || temp[y][x] == '1')
				game->map->map[y][x] = temp[y][x] - '0';
			else if (temp[y][x] == 'N' || temp[y][x] == 'W' || \
				temp[y][x] == 'S' || temp[y][x] == 'E')
			{
				game->map->map[y][x] = temp[y][x];
				cnt++;
			}
		}
	}
	return (cnt);
}

void	parse_map(t_game *game)
{
	char	**temp;
	int		cnt;

	temp = ft_split(game->map->map_temp, '\n');
	if (!temp)
		print_perror("allocated error");
	game->map->height = get_size(temp);
	game->map->width = get_maxlen(temp);
	game->map->map = (int **)malloc(sizeof(int *) * game->map->height);
	if (!game->map->map)
		print_perror("allocated error");
	cnt = trans_map(game, temp, 0);
	if (cnt != 1)
		print_error("invalid number of position size");
	free_str(temp);
}

int	check_num(t_map *map, int x, int y)
{
	if (y == map->height - 1 || x == map->width - 1 || x == 0 || y == 0)
		return (1);
	if (map->map[y - 1][x] == -1 || map->map[y + 1][x] == -1 || \
			map->map[y][x - 1] == -1 || map->map[y][x + 1] == -1)
		return (1);
	if (map->map[y - 1][x - 1] == -1 \
	|| map->map[y + 1][x + 1] == -1 || map->map[y + 1][x - 1] == -1 \
	|| map->map[y - 1][x + 1] == -1)
		return (1);
	return (0);
}

void	check_map(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] != -1 && map->map[y][x] != 1)
			{
				if (check_num(map, x, y))
				{
					print_error("invalid map");
				}
			}
			x++;
		}
		y++;
	}
}
