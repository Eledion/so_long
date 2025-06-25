/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:19:31 by marvin            #+#    #+#             */
/*   Updated: 2025/06/24 21:19:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/MLX42.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# include "get_next_line.h"
# include "ft_printf.h"

# define WIDTH 800
# define HEIGHT 600
# define TILE 64
# define INITIAL_MAP_CAPACITY 10
# define MAX_HEIGHT 100
# define MAX_WIDTH 100

typedef struct s_game
{
	void		*mlx;
	int			width;
	int			height;
	char		**map;
	int			px;
	int			py;
	int			ex;
	int			ey;
	int			moves;
	int			collected;
	int			total_collectibles;
	mlx_image_t	*floor_img;
	mlx_image_t	*wall_img;
	mlx_image_t	*player_img;
	mlx_image_t	*collectible_img;
	mlx_image_t	*exit_img;
}	t_game;

typedef struct s_map_counts
{
	int	p;
	int	e;
	int	c;
}	t_map_counts;

//main logic
void	count_collectibles(t_game *game);
void	load_images(t_game *g);
void	render_map(t_game *g);
void	close_window(void *param);
char	**read_map(const char *filename, int *height);
void	key_handler(mlx_key_data_t keydata, void *param);
void	find_player_position(t_game *game);
void	update_moves_text(t_game *game);
bool	validate_map(const char *filename, t_game *game);
bool	validate_playability(t_game *game);
void	flood_fill(char **map, int x, int y);
void	flood_fill_exit(char **map, int x, int y);
char	**clone_map(char **map, int height);

//utils
bool	has_ber_extension(const char *filename);
bool	report_error(const char *message);
void	free_map(char **map, int height);

//libft_utils
char	*ft_itoa(int n);
char	*ft_strdup(const char *s);
void	ft_putendl_fd(const char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
