/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   device_private.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:24:37 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/26 18:48:53 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEVICE_PRIVATE_H
# define DEVICE_PRIVATE_H

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

typedef struct	s_image
{
	void			*dv;
	void			*img;
	int				width;
	int				height;
	int				bpp;
	int				line_sz;
	unsigned char	*ptr;
}		t_image;

typedef struct	s_device
{
	void		*mlx;
	void		*winmlx;
	t_mouse		mouse;
	int			key;
	int			exposed;
	int			(*main_loop)();
	void		*main_loop_param;
}	t_device;

void	prepare_device_events(t_device *dv);
void	reset_device_events(t_device *dv);

int		loop_hook(t_device *dv);
int		expose_hook(t_device *dv);
int		key_hook(int keycode, t_device *dv);
int		mouse_hook(int button, int x, int y, t_device *dv);

#endif
