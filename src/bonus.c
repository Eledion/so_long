/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:42:41 by marvin            #+#    #+#             */
/*   Updated: 2025/06/24 16:42:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Makes sure that the graphic tile at (0,0) is redrawn before rendering.
static void	redraw_tile_under_text(t_game *game, int tile_x, int tile_y)
{
	float	fx;
	float	fy;
	char	tile;

	fx = tile_x * TILE;
	fy = tile_y * TILE;
	tile = game->map[tile_y][tile_x];
	mlx_image_to_window(game->mlx, game->floor_img, fx, fy);
	if (tile == '1')
		mlx_image_to_window(game->mlx, game->wall_img, fx, fy);
	else if (tile == 'C')
		mlx_image_to_window(game->mlx, game->collectible_img, fx, fy);
	else if (tile == 'E')
		mlx_image_to_window(game->mlx, game->exit_img, fx, fy);
	else if (tile == 'P')
		mlx_image_to_window(game->mlx, game->player_img, fx, fy);
}

// Update the moves in the text.
void	update_moves_text(t_game *game)
{
	char	*moves_str;

	moves_str = ft_itoa(game->moves);
	if (!moves_str)
		return ;
	redraw_tile_under_text(game, 0, 0);
	mlx_put_string(game->mlx, moves_str, 10, 10);
	free(moves_str);
}
