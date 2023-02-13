/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaittola <kaittola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 23:32:13 by kaittola          #+#    #+#             */
/*   Updated: 2022/10/17 23:09:44 by kaittola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_message(const char *msg, int v)
{
	ft_putstr(msg);
	exit(v);
}

int	exit_success(void)
{
	exit_message(EXIT_WINDOW, EXIT_SUCCESS);
	return (0);
}
