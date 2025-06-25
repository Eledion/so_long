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

// Check if the map has unreachable collectibles
static bool	has_unreachable_collectibles(char **map_copy, int height)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (map_copy[y][x])
		{
			if (map_copy[y][x] == 'C')
				return (true);
			x++;
		}
		y++;
	}
	return (false);
}

// Check if exit es reacheable.
static bool	check_exit_reached(char **map_copy, int height)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (map_copy[y][x])
		{
			if (map_copy[y][x] == 'E')
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

// Check if every collectible is reachable using flood fill.
bool	validate_collectibles(t_game *game)
{
	char	**map_copy;

	map_copy = clone_map(game->map, game->height);
	if (!map_copy)
		return (report_error("Failed to clone the map"));
	flood_fill(map_copy, game->px, game->py);
	if (has_unreachable_collectibles(map_copy, game->height))
	{
		free_map(map_copy, game->height);
		return (report_error("Not all collectibles are reachable"));
	}
	free_map(map_copy, game->height);
	return (true);
}

// Check if exit es reacheable using flood fill.
bool	validate_exit(t_game *game)
{
	char	**map_copy;

	map_copy = clone_map(game->map, game->height);
	if (!map_copy)
		return (report_error("Failed to clone the map"));
	flood_fill_exit(map_copy, game->px, game->py);
	if (!check_exit_reached(map_copy, game->height))
	{
		free_map(map_copy, game->height);
		return (report_error("Exit is not reachable after collecting"));
	}
	free_map(map_copy, game->height);
	return (true);
}

bool	validate_playability(t_game *game)
{
	return (validate_collectibles(game) && validate_exit(game));
}
