/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:32:29 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/26 20:55:36 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "device_private.h"
#include <mlx.h>

int		device_main_loop(t_device *dv, int (*f)(), void *param)
{
	dv->main_loop = f;
	dv->main_loop_param = param;
	mlx_loop_hook(dv->mlx, loop_hook, dv);
	mlx_loop(dv->mlx);
	return (1);
}

int		loop_hook(t_device *dv)
{
	prepare_device_events(dv);
	if (dv->main_loop)
		dv->main_loop(dv->main_loop_param);
	reset_device_events(dv);
	mlx_do_sync(dv->mlx);
	return (1);
}

int		expose_hook(t_device *dv)
{
	dv->exposed = 1;
	return (1);
}

int		key_hook(int keycode, t_device *dv)
{
	dv->key = (int)keycode;
	return (1);
}

int		mouse_hook(int button, int x, int y, t_device *dv)
{
	if (button == 1)
		dv->mouse.left = 1;
	else if (button == 2)
		dv->mouse.right = 1;
	else if (button == 3)
		dv->mouse.middle = 1;
	else if (button == 4 || button == 5)
		dv->mouse.scroll = (button - 4) * 2 - 1;
	(void)x, (void)y;
	return (1);
}
