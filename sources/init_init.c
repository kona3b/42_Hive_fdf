/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaittola <kaittola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:54:32 by kaittola          #+#    #+#             */
/*   Updated: 2022/10/19 03:28:31 by kaittola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
		exit_message(EXIT_MLX_1, EXIT_ERROR);
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, WIN_N);
	if (mlx->win == NULL)
		exit_message(EXIT_MLX_2, EXIT_ERROR);
}

static void	init_fdf(t_fdf *fdf)
{
	fdf->zoom = (int)max(WIN_H / (fdf->map.line_count * SPACING),
			WIN_W / (fdf->map.max_point_count * SPACING));
	fdf->zoom += !fdf->zoom;
	stick_zoom((unsigned int *)&fdf->zoom);
	init_origin(fdf);
	init_offset(fdf);
	fdf->height = 0.1;
	fdf->proj = PROJ_PARALLEL;
	fdf->color_theme = BLUE;
}

static void	init_mouse(t_program *program)
{
	program->mouse->prev = program->fdf->origin;
	program->mouse->curr = program->fdf->origin;
	program->mouse->diff = (t_point){.row = 0, .col = 0};
	program->mouse->isdown = FALSE;
}

void	init_req(t_program *program)
{
	init_mlx(program->mlx);
	init_fdf(program->fdf);
	init_mouse(program);
	mlx_do_key_autorepeaton(program->mlx);
}

void	init_img(t_mlx *mlx, t_fdf *fdf)
{
	(void)fdf;
	mlx->img.img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel, \
		&mlx->img.line_length, &mlx->img.endian);
}
