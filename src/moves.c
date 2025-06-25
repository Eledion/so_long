/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:38:38 by marvin            #+#    #+#             */
/*   Updated: 2025/06/23 19:38:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	can_move_to(t_game *game, int tx, int ty)
{
	char	dest;

	if (tx < 0 || tx >= game->width || ty < 0 || ty >= game->height)
		return (false);
	dest = game->map[ty][tx];
	if (dest == '1')
		return (false);
	if (dest == 'E' && game->collected < game->total_collectibles)
	{
		ft_printf("You still need %d collectibles!\n",
			game->total_collectibles - game->collected);
		return (false);
	}
	return (true);
}

static void	apply_movement(t_game *game, int tx, int ty)
{
	char	dest;

	dest = game->map[ty][tx];
	if (dest == 'C')
	{
		game->map[ty][tx] = '0';
		game->collected++;
	}
	mlx_image_to_window(game->mlx, game->floor_img,
		game->px * TILE, game->py * TILE);
	game->px = tx;
	game->py = ty;
	game->moves++;
	ft_printf("MOVES: %d\n", game->moves);
	update_moves_text(game);
	mlx_image_to_window(game->mlx, game->player_img,
		game->px * TILE, game->py * TILE);
	if (dest == 'E' && game->collected == game->total_collectibles)
	{
		ft_printf("You won in %d moves!\n", game->moves);
		mlx_close_window(game->mlx);
	}
}

static void	move_player(t_game *game, int dx, int dy)
{
	int	tx;
	int	ty;

	tx = game->px + dx;
	ty = game->py + dy;
	if (!can_move_to(game, tx, ty))
		return ;
	apply_movement(game, tx, ty);
}

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_W)
			move_player(game, 0, -1);
		else if (keydata.key == MLX_KEY_S)
			move_player(game, 0, 1);
		else if (keydata.key == MLX_KEY_A)
			move_player(game, -1, 0);
		else if (keydata.key == MLX_KEY_D)
			move_player(game, 1, 0);
		else if (keydata.key == MLX_KEY_ESCAPE)
			close_window(game);
	}
}
