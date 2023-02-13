/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaittola <kaittola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:08:08 by kaittola          #+#    #+#             */
/*   Updated: 2022/10/19 18:48:54 by kaittola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	map_line_count(t_map *map)
{
	t_row	*del_lines;
	int		temp;

	if (map->size > map->line_count)
		return ;
	del_lines = map->lines;
	temp = map->line_count * 3 / 2 + 1;
	if (temp < 0)
		exit_message(EXIT_MAP_SIZE, EXIT_ERROR);
	map->lines = (t_row *)malloc(sizeof(t_row) * (((size_t)temp) + 1));
	if (map->lines == NULL)
		exit_message(EXIT_MAP_MALLOC, EXIT_ERROR);
	if (del_lines != NULL)
		ft_memcpy(map->lines, del_lines, (size_t)map->size * sizeof(t_row));
	map->size = temp;
	free(del_lines);
}

static void	line_length(t_row *line)
{
	int		*del_line;
	int		temp;

	if (line->size > line->point_count)
		return ;
	del_line = line->line;
	temp = line->point_count * 3 / 2 + 1;
	if (temp < 0)
		exit_message(EXIT_LINES_1, EXIT_ERROR);
	line->line = (int *)malloc(sizeof(int) * (size_t)temp);
	if (line->line == NULL)
		exit_message(EXIT_LINES_2, EXIT_ERROR);
	if (del_line != NULL)
		ft_memcpy(line->line, del_line, (size_t)line->size * sizeof(int));
	line->size = temp;
	free(del_line);
}

static void	*free_splits(char **strings)
{
	char	**str_splits;
	char	*temp;

	str_splits = strings;
	while (*strings)
	{
		temp = *strings++;
		free(temp);
	}
	free(str_splits);
	return (NULL);
}

static void	add_line_to_map(t_map *map, char *line_string)
{
	char	**numerals;
	t_row	line;
	int		temp;

	ft_bzero(&line, sizeof(t_row));
	numerals = ft_strsplit(line_string, ' ');
	if (numerals == NULL)
		exit_message(EXIT_SPLIT, EXIT_ERROR);
	check_nbrs(numerals);
	while (numerals[line.point_count])
	{
		temp = ft_atoi(numerals[line.point_count]);
		line_length(&line);
		if (temp < -10000000 || temp > 10000000)
			temp = temp / 100;
		if (temp > map->height.max)
			map->height.max = temp;
		if (temp < map->height.min)
			map->height.min = temp;
		line.line[line.point_count++] = temp;
	}
	if (map->max_point_count < line.point_count)
		map->max_point_count = line.point_count;
	map->lines[map->line_count] = line;
	numerals = free_splits(numerals);
}

void	parse(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	int		status;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_message(EXIT_OPEN, EXIT_ERROR);
	while (1)
	{
		status = get_next_line(fd, &line);
		if (status < 0 || (status > 0 && line == NULL))
			exit_message(EXIT_GNL, EXIT_ERROR);
		else if (status == 0)
			break ;
		map_line_count(map);
		add_line_to_map(map, line);
		free(line);
		check_lines(map);
		map->line_count += (uint64_t) !!status;
	}
	if (map->size == 0)
		exit_message(EXIT_MAP_LINES, EXIT_ERROR);
	free(line);
	if (close(fd) < 0)
		exit_message(EXIT_CLOSE, EXIT_ERROR);
}
