/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:06:08 by marvin            #+#    #+#             */
/*   Updated: 2025/06/24 16:06:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Duplica un mapa para no modificar el original */
static char **clone_map(char **map, int height)
{
	char **copy = malloc(sizeof(char *) * (height + 1));
	int i = 0;

	if (!copy)
		return (NULL);
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[height] = NULL;
	return (copy);
}

void count_collectibles(t_game *game)
{
	int x, y;

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

void flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'F')
		return;

	map[y][x] = 'F';

	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

bool validate_playability(t_game *game)
{
	char **map_copy;
	int y;
	int x;

	map_copy = clone_map(game->map, game->height);
	if (!map_copy)
	{
		ft_putendl_fd("Error: no se pudo clonar el mapa", 2);
		return (false);
	}
	flood_fill(map_copy, game->px, game->py);
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (map_copy[y][x])
		{
			if (map_copy[y][x] == 'C' || map_copy[y][x] == 'E')
			{
				ft_putendl_fd("Error: not all collectibles or exit are reachable", 2);
				free_map(map_copy, game->height);
				return (false);
			}
			x++;
		}
		y++;
	}
	free_map(map_copy, game->height);
	return (true);
}