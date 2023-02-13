/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_and_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaittola <kaittola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:47:02 by kaittola          #+#    #+#             */
/*   Updated: 2022/10/19 02:19:28 by kaittola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	keys_handler(int key, t_program *program)
{
	if (key == KEY_ESC)
		exit_message(EXIT_ESC, EXIT_SUCCESS);
	if (key == KEY_C)
	{
		change_colors(program);
		draw(program->mlx, program->fdf);
	}
	if (key == KEY_P)
	{
		change_projection(program);
		draw(program->mlx, program->fdf);
	}
	if (key == UP_KEY)
	{
		program->fdf->height += 0.01;
		draw(program->mlx, program->fdf);
	}
	if (key == DOWN_KEY)
	{
		program->fdf->height -= 0.01;
		draw(program->mlx, program->fdf);
	}
	return (0);
}

int	mouse_handler(int button, int x, int y, t_program *program)
{
	(void) button;
	(void) x;
	(void) y;
	draw(program->mlx, program->fdf);
	return (RETURN_SUCCESS);
}
