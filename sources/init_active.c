/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_active.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaittola <kaittola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:29:01 by kaittola          #+#    #+#             */
/*   Updated: 2022/10/19 01:37:00 by kaittola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_origin(t_fdf *fdf)
{
	fdf->origin = (t_point){.row = (fdf->map.line_count - 1) * fdf->zoom / 2, \
		.col = (fdf->map.max_point_count - 1) * fdf->zoom / 2};
}

void	init_offset(t_fdf *fdf)
{
	fdf->offset = (t_point){.row = WIN_H / 2, .col = WIN_W / 2};
}
