/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   device.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:15:57 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/25 20:00:45 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEVICE_H
# define DEVICE_H

typedef struct	s_mouse
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		left;
	int		right;
	int		middle;
	int		scroll;
}		t_mouse;

void	*create_device(void);
void	free_device(void *dv);
int		create_window(void *dv, int width, int height, const char *title);

/*
** f(void *param)
*/
void	device_main_loop(void *dv, int (*f)(), void *param);

t_mouse	*get_device_mouse(void *dv);
int		get_device_key(void *dv);
int		is_device_exposed(void *dv);

#endif
