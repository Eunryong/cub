/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wocheon <wocheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:23:33 by wocheon           #+#    #+#             */
/*   Updated: 2023/02/14 16:43:11 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int argc, char **argv)
{
	t_game	game;
	t_mlx	mlx;

	if (argc != 2 || !filename_valid(argv[1]))
		print_error("invalid number of argument");
	init_mlx(&mlx);
	parse_data(&game, argv[1]);
	init_data(&game, &mlx);
	start_game(&game, &mlx);
	mlx_hook(mlx.win_ptr, 2, 0, key_hook, &game);
	mlx_hook(mlx.win_ptr, 17, 0, exit_hook, &game);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
