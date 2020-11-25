/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   device.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:41:05 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/25 20:27:02 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "device_private.h"
#include <libft.h>
#include <mlx.h>

t_device	*create_device(void)
{
	t_device	*dv;

	dv = (t_device *)ft_calloc(1, sizeof(t_device));
	if (dv != NULL)
	{
		dv->mlx = mlx_init();
		if (dv->mlx == NULL)
		{
			free(dv);
			dv = NULL;
		}
	}
	return (dv);
}

void		free_device(t_device *dv)
{
	if (dv->mlx)
		free(dv->mlx);
	if (dv->winmlx)
		free(dv->winmlx);
	dv->mlx = NULL;
	dv->winmlx = NULL;
	free(dv);
}

int			create_window(t_device *dv, int width, int height,
	const char *title)
{
	dv->winmlx = mlx_new_window(dv->mlx, width, height, (char *)title);
	return (dv->winmlx != NULL);
}
