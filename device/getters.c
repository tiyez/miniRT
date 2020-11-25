/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:50:34 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/25 19:52:29 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "device_private.h"

t_mouse	*get_device_mouse(t_device *dv)
{
	return (&dv->mouse);
}

int		get_device_key(t_device *dv)
{
	return (dv->key);
}

int		is_device_exposed(t_device *dv)
{
	return (dv->exposed);
}
