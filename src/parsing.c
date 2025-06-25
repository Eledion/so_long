/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:02:44 by marvin            #+#    #+#             */
/*   Updated: 2025/06/24 16:02:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	is_rectangular(char **map, int height)
{
	int		i;
	size_t	width;

	width = ft_strlen(map[0]);
	i = 1;
	while (i < height)
	{
		if (ft_strlen(map[i]) != width)
			return (false);
		i++;
	}
	return (true);
}

static bool	is_surrounded_by_walls(char **map, int width, int height)
{
	int	x;
	int	y;

	x = 0;
	while (x < width)
	{
		if (map[0][x] != '1' || map[height - 1][x] != '1')
			return (false);
		x++;
	}
	y = 0;
	while (y < height)
	{
		if (map[y][0] != '1' || map[y][width - 1] != '1')
			return (false);
		y++;
	}
	return (true);
}

static bool	has_valid_characters(char **map, int height)
{
	int			x;
	int			y;
	const char	*valid;

	valid = "01CEP";
	y = 0;
	while (y < height)
	{
		x = 0;
		while (map[y][x])
		{
			if (!ft_strchr(valid, map[y][x]))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

static bool	has_required_elements(char **map, int height, t_game *game)
{
	int				x;
	int				y;
	t_map_counts	counts;

	counts.p = 0;
	counts.e = 0;
	counts.c = 0;
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'P')
				counts.p++;
			else if (map[y][x] == 'E')
				counts.e++;
			else if (map[y][x] == 'C')
				counts.c++;
		}
	}
	game->total_collectibles = counts.c;
	return (counts.p == 1 && counts.e == 1 && counts.c >= 1);
}

bool	validate_map(const char *filename, t_game *game)
{
	if (game->height == 0 || !game->map || !game->map[0]
		|| game->map[0][0] == '\0')
		return (report_error("Map is empty"));
	if (!has_ber_extension(filename))
		return (report_error("File must have .ber extension"));
	game->width = ft_strlen(game->map[0]);
	if (!is_rectangular(game->map, game->height))
		return (report_error("Map is not rectangular"));
	if (!is_surrounded_by_walls(game->map, game->width, game->height))
		return (report_error("Map is not surrounded by walls"));
	if (!has_valid_characters(game->map, game->height))
		return (report_error("Map contains invalid characters"));
	if (!has_required_elements(game->map, game->height, game))
		return (report_error("Map must have 1 'P', 1 'E',and at least 1 'C'"));
	if (!validate_playability(game))
		return (false);
	return (true);
}
