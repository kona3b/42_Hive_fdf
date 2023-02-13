/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaittola <kaittola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:21:26 by kaittola          #+#    #+#             */
/*   Updated: 2022/10/19 01:21:29 by kaittola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	hooks(t_program *program)
{
	mlx_hook(program->mlx->win, ON_KEYDOWN, 0, keys_handler, program);
	mlx_hook(program->mlx->win, ON_DESTROY, 0, exit_success, program);
	mlx_hook(program->mlx->win, ON_MOUSEDOWN, 0, mouse_action_down, program);
	mlx_hook(program->mlx->win, ON_MOUSEMOVE, 0, mouse_action_move, program);
	mlx_hook(program->mlx->win, ON_MOUSEUP, 0, mouse_action_up, program);
}

int	main(int argc, char **argv)
{
	static t_mlx	mlx;
	static t_fdf	fdf;
	static t_mouse	mouse;
	t_program		program;

	if (argc != 2)
		exit_message(EXIT_USAGE, EXIT_ERROR);
	program = (t_program){.mlx = &mlx, .fdf = &fdf, .mouse = &mouse};
	fdf.map.height.max = INT_MIN;
	fdf.map.height.min = INT_MAX;
	parse(*(argv + 1), &program.fdf->map);
	init_req(&program);
	hooks(&program);
	draw(&mlx, &fdf);
	mlx_loop(program.mlx->mlx);
}
