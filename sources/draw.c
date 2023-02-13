/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaittola <kaittola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:57:42 by kaittola          #+#    #+#             */
/*   Updated: 2022/10/19 04:15:12 by kaittola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	compare_heights(t_point *point0, t_point *point1, t_fdf *fdf)
{
	if (fdf->map.lines[point0->row].line[point0->col]
		> fdf->map.lines[point1->row].line[point1->col])
		return (DO_SWAP);
	return (NO_SWAP);
}

static void	swap_points(t_point **point0, t_point **point1, int condition)
{
	t_point	*temp;

	if (condition == DO_SWAP)
	{
		temp = *point0;
		*point0 = *point1;
		*point1 = temp;
	}
}

static int	draw_line(t_segment *s, t_program *p, t_segment *o)
{
	t_double_coord	dt;
	t_double_coord	px;
	int				pxs;
	int				pt;

	swap_points(&s->b, &s->e, compare_heights(o->b, o->e, p->fdf));
	swap_points(&o->b, &o->e, compare_heights(o->b, o->e, p->fdf));
	dt = (t_double_coord){.row = s->e->row - s->b->row,
		.col = s->e->col - s->b->col};
	pxs = (int)sqrt(dt.row * dt.row + dt.col * dt.col);
	if (pxs == 0)
		return (RETURN_SUCCESS);
	dt = (t_double_coord){.row = dt.row / pxs, .col = dt.col / pxs};
	px = (t_double_coord){.row = s->b->row, .col = s->b->col};
	pt = 0;
	while (pt <= pxs)
	{
		if (in_range(0, (int)px.row, WIN_H) && in_range(0, (int)px.col, WIN_W))
			my_mlx_pixel_put(&p->mlx->img, (int)px.col, (int)px.row,
				get_color((double)pt / pxs, o, p->fdf));
		px = (t_double_coord){.row = px.row + dt.row, .col = px.col + dt.col};
		pt++;
	}
	return (RETURN_SUCCESS);
}

static void	segment_feeder(t_mlx *mlx, t_fdf *fdf, t_point *point)
{
	t_point	p0;
	t_point	p1;

	projection(&p0, point, fdf);
	if (point->col + 1 < fdf->map.lines[point->row].point_count)
	{
		projection(&p1, &(t_point){
			.row = point->row, .col = point->col + 1}, fdf);
		draw_line(&(t_segment){&p0, &p1}, &(t_program){
			mlx, fdf, 0}, &(t_segment){point, &(t_point){
			.row = point->row, .col = point->col + 1}});
	}
	if (point->row + 1 < fdf->map.line_count)
	{
		projection(&p1, &(t_point){.row = point->row + 1,
			.col = point->col}, fdf);
		draw_line(&(t_segment){&p0, &p1}, &(t_program){
			mlx, fdf, 0}, &(t_segment){point, &(t_point){
			.row = point->row + 1, .col = point->col}});
	}
}

void	draw(t_mlx *mlx, t_fdf *fdf)
{
	t_point	point;

	init_img(mlx, fdf);
	point.row = 0;
	while (point.row < fdf->map.line_count)
	{
		point.col = 0;
		while (point.col < fdf->map.lines[point.row].point_count)
		{
			segment_feeder(mlx, fdf, &point);
			point.col++;
		}
		point.row++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	print_menu(mlx);
	mlx_destroy_image(mlx->mlx, mlx->img.img);
}
