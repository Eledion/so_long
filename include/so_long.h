#ifndef SO_LONG_H
# define SO_LONG_H

// Librerías externas
# include "MLX42/MLX42.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

// Librerías propias
# include "get_next_line.h"
# include "ft_printf.h"

// Constantes para ventana y tamaño de tile
# define WIDTH 800
# define HEIGHT 600
# define TILE 64
# define INITIAL_MAP_CAPACITY 10

#define MAX_HEIGHT 100
#define MAX_WIDTH 100

typedef struct s_game
{
    void    *mlx;
    int     width;
    int     height;

    char    **map;
    int     px;     // posición jugador X (columna)
    int     py;     // posición jugador Y (fila)

    int     ex;     // posición salida X
    int     ey;     // posición salida Y

    int     moves;              // contador de pasos
    int     collected;          // cuántos C llevas
    int     total_collectibles; // total de C en el mapa

    mlx_image_t *floor_img;
    mlx_image_t *wall_img;
    mlx_image_t *player_img;
    mlx_image_t *collectible_img;
    mlx_image_t *exit_img;
}   t_game;

typedef struct s_map_counts
{
    int p;
    int e;
    int c;
} t_map_counts;


void count_collectibles(t_game *game);
void load_images(t_game *g);
void render_map(t_game *g);
void move_player(t_game *g, int dx, int dy);
bool	validate_map(t_game *game);
bool	validate_playability(t_game *game);


// Prototipos de funciones
void    close_window(void *param);
char    **read_map(const char *filename, int *height);
void    print_map(char **map, int height, int index);
void    load_assets(t_game *game);
void    render_map(t_game *game);
void    key_handler(mlx_key_data_t keydata, void *param);
void    find_player_position(t_game *game);
void update_moves_text(t_game *game);

bool	report_error(const char *message);

void    free_map(char **map, int height);

char	*ft_itoa(int n);
char	*ft_strdup(const char *s);
void	ft_putendl_fd(const char *s, int fd);

#endif

