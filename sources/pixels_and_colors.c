/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_and_colors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaittola <kaittola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 23:34:43 by kaittola          #+#    #+#             */
/*   Updated: 2022/10/19 13:44:58 by kaittola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

void	change_projection(t_program *program)
{
	if (program->fdf->proj == PROJ_PARALLEL)
		program->fdf->proj = PROJ_ISOMETRIC;
	else if (program->fdf->proj == PROJ_ISOMETRIC)
		program->fdf->proj = PROJ_MILITARY;
	else if (program->fdf->proj == PROJ_MILITARY)
		program->fdf->proj = PROJ_PARALLEL;
}

void	change_colors(t_program *program)
{
	if (program->fdf->color_theme == RED)
		program->fdf->color_theme = GREEN;
	else if (program->fdf->color_theme == GREEN)
		program->fdf->color_theme = BLUE;
	else if (program->fdf->color_theme == BLUE)
		program->fdf->color_theme = RED;
}

static double	skew(double min, double percent, double max)
{
	return (min + percent * (1 - min) / max);
}

int	get_color(double percent, t_segment *points, t_fdf *fdf)
{
	long		max_height;
	double		height_percent;
	int			color_temp;
	long		alt_div;

	max_height = get_height(
			abs_max(fdf->map.lines[points->b->row].line[points->b->col],
				fdf->map.lines[points->e->row].line[points->e->col]), fdf);
	if (max_height == 0)
		return ((int)(0xFF * LOWEST) << fdf->color_theme);
	alt_div = get_height(fdf->map.height.max - fdf->map.height.min, fdf);
	height_percent = (double)max_height / (alt_div + !alt_div * max_height);
	if (fdf->map.lines[points->b->row].line[points->b->col]
		!= fdf->map.lines[points->e->row].line[points->e->col])
			color_temp = (int)(0xFF * skew(LOWEST, percent
					* height_percent, HIGHEST)) << fdf->color_theme;
	else
		color_temp = (int)(0xFF * height_percent) << fdf->color_theme;
	if (color_temp != 0)
		return (color_temp);
	return ((int)(0xFF * LOWEST) << fdf->color_theme);
}
