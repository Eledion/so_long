/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:55:15 by marvin            #+#    #+#             */
/*   Updated: 2025/06/23 11:55:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_collectibles(t_game *game)
{
	int	x;
	int	y;

	game->total_collectibles = 0;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'C')
				game->total_collectibles++;
			x++;
		}
		y++;
	}
}

static bool	load_map_and_prepare(t_game *game, char *map_file)
{
	game->height = 0;
	ft_printf("Opening map...\n");
	game->map = read_map(map_file, &game->height);
	if (!game->map)
	{
		ft_putendl_fd("Error reading the map", 2);
		return (false);
	}
	game->width = ft_strlen(game->map[0]);
	game->total_collectibles = 0;
	game->collected = 0;
	game->moves = 0;
	find_player_position(game);
	count_collectibles(game);
	if (!validate_map(map_file, game))
	{
		free_map(game->map, game->height);
		return (false);
	}
	return (true);
}

static bool	init_game(t_game *game, char *map_file)
{
	if (!load_map_and_prepare(game, map_file))
		return (false);
	game->mlx = mlx_init(game->width * TILE,
			game->height * TILE, "so_long", false);
	if (!game->mlx)
	{
		free_map(game->map, game->height);
		return (false);
	}
	load_images(game);
	return (true);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./so_long <map.ber>", 2);
		return (EXIT_FAILURE);
	}
	if (!init_game(&game, argv[1]))
		return (EXIT_FAILURE);
	render_map(&game);
	ft_printf("Map successfully loaded\n");
	update_moves_text(&game);
	mlx_key_hook(game.mlx, key_handler, &game);
	mlx_close_hook(game.mlx, close_window, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
