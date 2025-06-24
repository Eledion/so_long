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

void load_images(t_game *g)
{
    mlx_texture_t *t;

    t = mlx_load_png("assets/grass.png");
    g->floor_img = mlx_texture_to_image(g->mlx, t);
    mlx_resize_image(g->floor_img, TILE, TILE);
    mlx_delete_texture(t);

    t = mlx_load_png("assets/tree.png");
    g->wall_img = mlx_texture_to_image(g->mlx, t);
    mlx_resize_image(g->wall_img, TILE, TILE);
    mlx_delete_texture(t);

    t = mlx_load_png("assets/berry.png");
    g->collectible_img = mlx_texture_to_image(g->mlx, t);
    mlx_resize_image(g->collectible_img, 34, 34);
    mlx_delete_texture(t);

    t = mlx_load_png("assets/umbreon.png");
    g->exit_img = mlx_texture_to_image(g->mlx, t);
    mlx_resize_image(g->exit_img, 80, 80);
    mlx_delete_texture(t);

    t = mlx_load_png("assets/eevee.png");
    g->player_img = mlx_texture_to_image(g->mlx, t);
    mlx_resize_image(g->player_img, 75, 75);
    mlx_delete_texture(t);
}

void draw_image_centered(t_game *g, mlx_image_t *img, int tile_x, int tile_y, int tile_size)
{
    int img_w = img->width;
    int img_h = img->height;

    int offset_x = (tile_size - img_w) / 2;
    int offset_y = (tile_size - img_h) / 2;

    float fx = tile_x * tile_size + offset_x;
    float fy = tile_y * tile_size + offset_y;

    mlx_image_to_window(g->mlx, img, fx, fy);
}


void render_map(t_game *g)
{
    int x, y;

    y = 0;
    while (y < g->height)
    {
        x = 0;
        while (x < g->width)
        {
            // Dibuja suelo siempre igual
            mlx_image_to_window(g->mlx, g->floor_img, x * TILE, y * TILE);

            if (g->map[y][x] == '1')
                draw_image_centered(g, g->wall_img, x, y, TILE);
            else if (g->map[y][x] == 'C')
                draw_image_centered(g, g->collectible_img, x, y, TILE);
            else if (g->map[y][x] == 'E')
                draw_image_centered(g, g->exit_img, x, y, TILE);

            x++;
        }
        y++;
    }

    // Dibuja jugador centrado en su tile también, si quieres
    draw_image_centered(g, g->player_img, g->px, g->py, TILE);
}


void	find_player_position(t_game *game)
{
	int	x, y;

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
				return; // ¡Salimos en cuanto lo encontramos!
			}
			x++;
		}
		y++;
	}
	ft_putendl_fd("Error: no se encontró al jugador en el mapa", 2);
}
