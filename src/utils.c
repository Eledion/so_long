/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:43:43 by marvin            #+#    #+#             */
/*   Updated: 2025/06/23 20:43:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	report_error(const char *message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
	return (false);
}

void	free_map(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
		free(map[i++]);
	free(map);
}

void	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	free_map(game->map, game->height);
	exit(EXIT_SUCCESS);
}

bool	has_ber_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (false);
	return (ft_strncmp(&filename[len - 4], ".ber", 4) == 0);
}

void	find_player_position(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
			{
				game->px = x;
				game->py = y;
				return ;
			}
			x++;
		}
		y++;
	}
}
