/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaittola <kaittola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 21:24:08 by kaittola          #+#    #+#             */
/*   Updated: 2022/10/19 18:49:30 by kaittola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_projection_angle(t_fdf *fdf)
{
	return (PROJ_ISOMETRIC + DIFF_ISO_MIL * !!(fdf->proj == PROJ_MILITARY));
}

void	projection(t_point *dst, t_point *scr, t_fdf *fdf)
{
	int	screen_row;
	int	screen_col;
	int	ordinate;
	int	abscissa;
	int	height;

	if (fdf->proj == PROJ_PARALLEL)
	{
		*dst = (t_point){
			.row = (scr->row * fdf->zoom + fdf->offset.row) - fdf->origin.row,
			.col = (scr->col * fdf->zoom + fdf->offset.col) - fdf->origin.col};
		return ;
	}
	ordinate = scr->row * fdf->zoom - fdf->origin.row;
	abscissa = scr->col * fdf->zoom - fdf->origin.col;
	height = get_height(fdf->map.lines[scr->row].line[scr->col], fdf);
	screen_row = (int)((-height) + (abscissa + ordinate)
			*sin(M_PI * get_projection_angle(fdf) / 180));
	screen_col = (int)((abscissa - ordinate)
			*cos(M_PI * get_projection_angle(fdf) / 180));
	*dst = (t_point){.row = screen_row + fdf->offset.row,
		.col = screen_col + fdf->offset.col};
}
