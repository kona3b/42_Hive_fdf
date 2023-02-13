/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaittola <kaittola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:31:22 by kaittola          #+#    #+#             */
/*   Updated: 2022/10/19 15:12:56 by kaittola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_lines(t_map *map)
{
	if (map->line_count > 0 && map->lines[map->line_count - 1].point_count \
		!= map->lines[map->line_count].point_count)
		exit_message(EXIT_LINES_0, EXIT_ERROR);
}

void	check_nbrs(char **numerals)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (numerals[j] != NULL)
	{
		while (numerals[j][i] != '\0')
		{
			if (numerals[j][i] == '-')
				i++;
			if (ft_isdigit(numerals[j][i]) == 0)
				exit_message(EXIT_MAP_LINES2, EXIT_ERROR);
			i++;
		}
		i = 0;
		j++;
	}
}
