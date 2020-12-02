/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:31:22 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/26 19:59:29 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "device_private.h"
#include <mlx.h>

void	prepare_device_events(t_device *dv)
{
	int		x;
	int		y;

	mlx_mouse_get_pos(dv->winmlx, &x, &y);
	dv->mouse.dx = x - dv->mouse.x;
	dv->mouse.dy = y - dv->mouse.y;
	dv->mouse.x = x;
	dv->mouse.y = y;
}

void	reset_device_events(t_device *dv)
{
	dv->exposed = 0;
	dv->key = -1;
	dv->mouse.left = 0;
	dv->mouse.right = 0;
	dv->mouse.middle = 0;
	dv->mouse.scroll = 0;
}
