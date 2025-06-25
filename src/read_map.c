/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:55:12 by marvin            #+#    #+#             */
/*   Updated: 2025/06/23 11:55:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//Delete invisibles characters.
static void	trim_trailing_whitespace(char *line)
{
	int	len;

	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'
			|| line[len - 1] == ' '))
	{
		line[--len] = '\0';
	}
}

//Double the size of the map array if there is no more space.
static char	**resize_buffer_if_needed(char **map, int *alloc, int used)
{
	char	**new_map;
	int		i;

	*alloc *= 2;
	new_map = malloc(sizeof(char *) * (*alloc));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < used)
	{
		new_map[i] = map[i];
		i++;
	}
	free(map);
	return (new_map);
}

//Clean, validate, and add a read line to the map array.
static char	**append_clean_line(char **map, char *line, int *count, int *alloc)
{
	trim_trailing_whitespace(line);
	if (line[0] == '\0')
	{
		free(line);
		return (map);
	}
	if (*count >= *alloc)
	{
		map = resize_buffer_if_needed(map, alloc, *count);
		if (!map)
		{
			free(line);
			return (NULL);
		}
	}
	map[(*count)++] = line;
	return (map);
}

//Load all lines from the file into memory.
static char	**load_map_lines(int fd, int *height)
{
	char	*line;
	char	**map;
	int		lines_count;
	int		lines_alloc;

	lines_count = 0;
	lines_alloc = 10;
	map = malloc(sizeof(char *) * INITIAL_MAP_CAPACITY);
	if (!map)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		map = append_clean_line(map, line, &lines_count, &lines_alloc);
		if (!map)
			break ;
		line = get_next_line(fd);
	}
	*height = lines_count;
	return (map);
}

//General entry point for reading a map.
char	**read_map(const char *filename, int *height)
{
	int		fd;
	char	**map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("\nError: could not open the file %s\n", filename);
		return (NULL);
	}
	else
		ft_printf("File %s opened successfully\n", filename);
	map = load_map_lines(fd, height);
	close(fd);
	return (map);
}
