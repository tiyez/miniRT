/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:21:59 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 16:22:38 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	movement(t_v3 pos, t_v4 xangle, int key)
{
	t_v3		axis[3];

	ft_make_xangle_axis(xangle, axis[0], axis[1], axis[2]);
	if (key == KEY_A)
		ft_mulvs_add_v3(axis[0], -0.1f, pos, pos);
	if (key == KEY_D)
		ft_mulvs_add_v3(axis[0], 0.1f, pos, pos);
	if (key == KEY_W)
		ft_mulvs_add_v3(axis[2], -0.1f, pos, pos);
	if (key == KEY_S)
		ft_mulvs_add_v3(axis[2], 0.1f, pos, pos);
	if (key == KEY_Q)
		ft_mulvs_add_v3(axis[1], -0.1f, pos, pos);
	if (key == KEY_E)
		ft_mulvs_add_v3(axis[1], 0.1f, pos, pos);
}

void	rotation(t_v4 xangle, int key)
{
	if (key == KEY_I)
		ft_rotate_xangle(xangle, -FT_RAD(10), 0);
	if (key == KEY_K)
		ft_rotate_xangle(xangle, FT_RAD(10), 0);
	if (key == KEY_J)
		ft_rotate_xangle(xangle, 0, -FT_RAD(10));
	if (key == KEY_L)
		ft_rotate_xangle(xangle, 0, FT_RAD(10));
}

void	movement_and_rotation(t_v3 pos, t_v4 xangle, int key)
{
	movement(pos, xangle, key);
	rotation(xangle, key);
}

void	movement_and_rotation_dir(t_v3 pos, t_v3 dir, int key)
{
	t_v4	xangle;

	ft_make_xangle_dir(dir, xangle);
	movement_and_rotation(pos, xangle, key);
	ft_make_dir_xangle(xangle, dir);
	ft_ext_normalize_v3(dir);
}

void	move_object(t_select *sel, int key)
{
	t_v3	pos;

	if (sel->type == SELECT_LIGHT)
		movement(sel->l->pos, (t_v4){0, 0, 1, 0}, key);
	else if (sel->type == SELECT_SPHERE)
		movement(sel->sp->pos, (t_v4){0, 0, 1, 0}, key);
	else if (sel->type == SELECT_PLANE)
		movement_and_rotation_dir(sel->pl->pos, sel->pl->normal, key);
	else if (sel->type == SELECT_SQUARE)
	{
		get_square_pos(sel->sq, pos);
		movement_and_rotation_dir(pos, sel->sq->normal, key);
		create_square(sel->sq, pos, get_square_side(sel->sq), sel->sq->normal);
	}
	else if (sel->type == SELECT_CYLINDER)
		movement_and_rotation_dir(sel->cy->pos, sel->cy->normal, key);
	else if (sel->type == SELECT_TRIANGLE)
	{
		movement(sel->tr->pos[0], (t_v4){0, 0, 1, 0}, key);
		movement(sel->tr->pos[1], (t_v4){0, 0, 1, 0}, key);
		movement(sel->tr->pos[2], (t_v4){0, 0, 1, 0}, key);
	}
}
