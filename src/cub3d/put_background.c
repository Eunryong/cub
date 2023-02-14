/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_background.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:35:02 by wocheon           #+#    #+#             */
/*   Updated: 2023/02/12 22:32:46 by wocheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	bg_pixel_put(t_image image, int x, int y, int color)
{
	char	*dst;

	dst = image.addr + (y * image.size_line + x * (image.bpp / 8));
	*(unsigned int *)dst = color;
}

void	put_background(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT - 1)
	{
		j = 0;
		while (j < WIN_WIDTH - 1)
		{
			if (i < WIN_HEIGHT / 2)
				bg_pixel_put(game->mlx->image, j, i, game->bgcolor->ceiling);
			else
				bg_pixel_put(game->mlx->image, j, i, game->bgcolor->floor);
			j++;
		}
		i++;
	}
}
