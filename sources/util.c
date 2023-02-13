/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaittola <kaittola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:10:09 by kaittola          #+#    #+#             */
/*   Updated: 2022/10/19 16:02:32 by kaittola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	in_range(int lowest, int value, int max)
{
	return (lowest <= value && value <= max);
}

double	max(double d0, double d1)
{
	if (d0 > d1)
		return (d0);
	return (d1);
}

int	abs_max(int i0, int i1)
{
	i1 *= (i1 < 0) * -1 | 0x1;
	i0 *= (i0 < 0) * -1 | 0x1;
	if (i1 > i0)
		return (i1);
	return (i0);
}

int	get_height(int height, t_fdf *fdf)
{
	return ((int)(height * fdf->height * fdf->zoom));
}
