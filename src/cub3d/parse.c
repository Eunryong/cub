/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:00:30 by wocheon           #+#    #+#             */
/*   Updated: 2023/02/13 16:19:22 by wocheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_type(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (!game->text[i].path)
			print_error("invalid number of texture");
	}
	if (game->bgcolor->ceiling == -1 || game->bgcolor->floor == -1)
		print_error("no ceiling or floor color");
}

void	read_file(t_game *game, char *file, int fd)
{
	char	*line;
	int		type;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		print_error(file);
	line = 0;
	while (1)
	{
		if (line)
			free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n')
			continue ;
		type = get_type(line);
		if (type == -1)
			print_error("invalid map");
		parse_line(game, line, type);
	}
	close(fd);
}

void	parse_text(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->text[i].img.img = mlx_xpm_file_to_image(game->mlx->mlx_ptr, \
			game->text[i].path, &game->text[i].width, &game->text[i].height);
		if (!game->text[i].img.img)
			print_error("fail to open texture file");
		game->text[i].data = (int *)mlx_get_data_addr(game->text[i].img.img, \
			&game->text[i].img.bpp, &game->text[i].img.size_line, \
			&game->text[i].img.endian);
		i++;
	}
}

void	parse_data(t_game *game, char *file)
{
	init_game(game);
	read_file(game, file, 0);
	if (!game->map->map_temp)
		print_error("invalid map");
	parse_map(game);
	check_type(game);
	check_map(game->map);
}
