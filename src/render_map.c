/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:55:44 by marvin            #+#    #+#             */
/*   Updated: 2025/06/23 12:55:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_images(t_game *g)
{
	mlx_texture_t	*t;

	t = mlx_load_png("textures/grass.png");
	g->floor_img = mlx_texture_to_image(g->mlx, t);
	mlx_resize_image(g->floor_img, TILE, TILE);
	mlx_delete_texture(t);
	t = mlx_load_png("textures/tree.png");
	g->wall_img = mlx_texture_to_image(g->mlx, t);
	mlx_resize_image(g->wall_img, TILE, TILE);
	mlx_delete_texture(t);
	t = mlx_load_png("textures/berry.png");
	g->collectible_img = mlx_texture_to_image(g->mlx, t);
	mlx_resize_image(g->collectible_img, TILE, TILE);
	mlx_delete_texture(t);
	t = mlx_load_png("textures/umbreon.png");
	g->exit_img = mlx_texture_to_image(g->mlx, t);
	mlx_resize_image(g->exit_img, 80, 80);
	mlx_delete_texture(t);
	t = mlx_load_png("textures/eevee.png");
	g->player_img = mlx_texture_to_image(g->mlx, t);
	mlx_resize_image(g->player_img, 75, 75);
	mlx_delete_texture(t);
}

void	render_map(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->height)
	{
		x = 0;
		while (x < g->width)
		{
			mlx_image_to_window(g->mlx, g->floor_img, x * TILE, y * TILE);
			if (g->map[y][x] == '1')
				mlx_image_to_window(g->mlx, g->wall_img, x * TILE, y * TILE);
			else if (g->map[y][x] == 'C')
				mlx_image_to_window(g->mlx,
					g->collectible_img, x * TILE, y * TILE);
			else if (g->map[y][x] == 'E')
				mlx_image_to_window(g->mlx, g->exit_img, x * TILE, y * TILE);
			x++;
		}
		y++;
	}
	mlx_image_to_window(g->mlx, g->player_img, g->px * TILE, g->py * TILE);
}
