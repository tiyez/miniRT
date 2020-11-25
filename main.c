/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:17:24 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/25 18:30:35 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniLibX/mlx.h"
#include "libft/libft.h"
#include <stdio.h>

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
}	t_mouse;

typedef struct	s_super
{
	void		*mlx;
	void		*winmlx;
	t_mouse		mouse;
	int			key;
	int			exposed;
}	t_super;

void	prepare_super_events(t_super *super)
{
	int		x;
	int		y;

	mlx_mouse_get_pos(super->winmlx, &x, &y);
	super->mouse.dx = x - super->mouse.x;
	super->mouse.dy = y - super->mouse.y;
	super->mouse.x = x;
	super->mouse.y = y;
}

void	reset_super_events(t_super *super)
{
	super->exposed = 0;
	super->key = -1;
	super->mouse.left = 0;
	super->mouse.right = 0;
	super->mouse.middle = 0;
	super->mouse.scroll = 0;
}

void	free_super(t_super **psuper)
{
	if (*psuper)
	{
		if ((*psuper)->mlx)
			free((*psuper)->mlx);
		if ((*psuper)->winmlx)
			free((*psuper)->winmlx);
		free(*psuper);
	}
	*psuper = 0;
}

int		loop_hook(t_super *super)
{
	prepare_super_events(super);
	reset_super_events(super);
	return (1);
}

int		expose_hook(t_super *super)
{
	super->exposed = 1;
	printf("expose\n");
	return (1);
}

int		key_hook(int keycode, t_super *super)
{
	super->key = keycode;
	printf("key: %d (%c)\n", keycode, (char)keycode);
	return (1);
}

int		mouse_hook(int button, int x, int y, t_super *super)
{
	if (button == 1)
		super->mouse.left = 1;
	else if (button == 2)
		super->mouse.right = 1;
	else if (button == 3)
		super->mouse.middle = 1;
	else if (button == 4 || button == 5)
		super->mouse.scroll = (button - 4) * 2 - 1;
	printf("mouse: btn: %d; x: %d; y: %d; scroll: %d;\n", button, x, y, super->mouse.scroll);
	return (1);
}

int		main()
{
	t_super	*super;

	if ((super = ft_calloc(1, sizeof(t_super))))
	{
		if ((super->mlx = mlx_init()))
		{
			if ((super->winmlx = mlx_new_window(super->mlx,
				800, 600, "Hello world!")))
			{
				mlx_mouse_hook(super->winmlx, mouse_hook, super);
				mlx_key_hook(super->winmlx, key_hook, super);
				mlx_expose_hook(super->winmlx, expose_hook, super);
				mlx_loop_hook(super->mlx, loop_hook, super);
				mlx_loop(super->mlx);
			}
		}
	}
	free_super(&super);
}

