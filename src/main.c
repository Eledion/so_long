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

void	free_map(char **map, int height)
{
	int i = 0;
	while (i < height)
		free(map[i++]);
	free(map);
}

void close_window(void *param)
{
	t_game *game = (t_game *)param;

	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	free_map(game->map, game->height);
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putendl_fd("Uso: ./so_long <mapa.ber>", 2);
		return (EXIT_FAILURE);
	}
	game.height = 0;
	ft_printf("Abriendo mapa...\n");
	game.map = read_map(argv[1], &game.height);
	if (!game.map)
	{
		ft_putendl_fd("Error leyendo el mapa", 2);
		return (EXIT_FAILURE);
	}
	game.width = ft_strlen(game.map[0]);
	game.total_collectibles = 0;
	game.collected = 0;
	game.moves = 0;
	find_player_position(&game);
	count_collectibles(&game);
	if (!validate_map(&game)) 
	{
		free_map(game.map, game.height);
		return (EXIT_FAILURE);
	}
	game.mlx = mlx_init(game.width * TILE, game.height * TILE, "so_long", false);
	if (!game.mlx)
	{
		free_map(game.map, game.height);
		return (EXIT_FAILURE);
	}
	load_images(&game);
	render_map(&game);
	update_moves_text(&game);
	mlx_key_hook(game.mlx, key_handler, &game);
	mlx_close_hook(game.mlx, close_window, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}