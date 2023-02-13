/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaittola <kaittola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:34:31 by kaittola          #+#    #+#             */
/*   Updated: 2022/10/14 21:57:47 by kaittola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	mouse_action_scroll_up(t_program *program, t_point *mouse)
{
	int	prev_zoom;

	prev_zoom = program->fdf->zoom;
	program->fdf->zoom = zoomer(ZOOM_IN, program->fdf->zoom);
	offsetter(mouse, program, prev_zoom);
	init_origin(program->fdf);
	draw(program->mlx, program->fdf);
	return (RETURN_SUCCESS);
}

static int	mouse_action_scroll_down(t_program *program, t_point *mouse)
{
	int	prev_zoom;

	prev_zoom = program->fdf->zoom;
	program->fdf->zoom = zoomer(ZOOM_OUT, program->fdf->zoom);
	offsetter(mouse, program, prev_zoom);
	init_origin(program->fdf);
	draw(program->mlx, program->fdf);
	return (RETURN_SUCCESS);
}

int	mouse_action_down(int button, int x, int y, t_program *program)
{
	if (button == LEFT_CLICK)
	{
		program->mouse->prev = program->mouse->curr;
		program->mouse->curr = (t_point){.row = y, .col = x};
		program->mouse->isdown = TRUE;
		return (mouse_handler(button, x, y, program));
	}
	if (button == SCROLL_UP)
		return (mouse_action_scroll_up(program, \
			&(t_point){.row = y, .col = x}));
	if (button == SCROLL_DOWN)
		return (mouse_action_scroll_down(program, \
			&(t_point){.row = y, .col = x}));
	return (RETURN_ERROR);
}

int	mouse_action_move(int x, int y, t_program *program)
{
	if (program->mouse->isdown == TRUE)
	{
		program->mouse->prev = program->mouse->curr;
		program->mouse->diff = (t_point){.row = y - program->mouse->curr.row, \
			.col = x - program->mouse->curr.col};
		pan(program);
		program->mouse->curr = (t_point){.row = y, .col = x};
		return (mouse_handler(MOVE, x, y, program));
	}
	return (RETURN_ERROR);
}

int	mouse_action_up(int button, int x, int y, t_program *program)
{
	if (button == LEFT_CLICK)
	{
		program->mouse->prev = program->mouse->curr;
		program->mouse->isdown = FALSE;
		return (mouse_handler(button, x, y, program));
	}
	return (RETURN_ERROR);
}
