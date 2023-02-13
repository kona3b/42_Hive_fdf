/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaittola <kaittola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 23:29:05 by kaittola          #+#    #+#             */
/*   Updated: 2022/10/19 01:43:11 by kaittola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	zoomer(int dir, int zoom)
{
	if (dir == ZOOM_IN)
	{
		if ((zoom << 1) >> 1 == zoom)
			return (zoom << 1);
	}
	else if (dir == ZOOM_OUT)
	{
		if ((zoom >> 1) << 1 == zoom)
			return (zoom >> 1);
	}
	return (zoom);
}

void	pan(t_program *program)
{
	program->fdf->offset = (t_point){
		.row = program->fdf->offset.row + program->mouse->diff.row,
		.col = program->fdf->offset.col + program->mouse->diff.col};
}

void	offsetter(t_point *mouse, t_program *program, int prev_zoom)
{
	t_point	prev_mouse;
	t_point	new_mouse;

	prev_mouse = (t_point){
		.row = (mouse->row - program->fdf->offset.row) / prev_zoom,
		.col = (mouse->col - program->fdf->offset.col) / prev_zoom};
	new_mouse = (t_point){
		.row = (mouse->row - program->fdf->offset.row) / program->fdf->zoom,
		.col = (mouse->col - program->fdf->offset.col) / program->fdf->zoom};
	program->fdf->offset = (t_point){
		.row = (new_mouse.row - prev_mouse.row) * program->fdf->zoom
		+ program->fdf->offset.row,
		.col = (new_mouse.col - prev_mouse.col) * program->fdf->zoom
		+ program->fdf->offset.col};
}

void	stick_zoom(unsigned int *zoom)
{
	unsigned char	c;

	c = 0;
	while (*zoom >> c != 0)
		c++;
	if (c > 0)
		*zoom &= (0x1U << --c);
}

void	print_menu(t_mlx *mlx)
{
	int		y;

	y = 0;
	mlx_string_put(mlx->mlx, mlx->win, 65, y += 20, TXT, "How to Use");
	mlx_string_put(mlx->mlx, mlx->win, 15, y += 35, TXT, "Zoom: mouse scroll");
	mlx_string_put(mlx->mlx, mlx->win, 15, y += 30, TXT, "Move: click + drag");
	mlx_string_put(mlx->mlx, mlx->win, 15, y += 30, TXT, "Projection change:");
	mlx_string_put(mlx->mlx, mlx->win, 15, y += 25, TXT, "P key");
	mlx_string_put(mlx->mlx, mlx->win, 15, y += 30, TXT, "Color change:");
	mlx_string_put(mlx->mlx, mlx->win, 15, y += 25, TXT, "C key");
	mlx_string_put(mlx->mlx, mlx->win, 15, y += 30, TXT, "UP and DOWN arrows:");
	mlx_string_put(mlx->mlx, mlx->win, 15, y += 25, TXT, "Edit scale");
	mlx_string_put(mlx->mlx, mlx->win, 15, y += 40, TXT, "Press ESC to exit");
}
