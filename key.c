/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:37:08 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 17:05:53 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	increment_object_param(t_select *sel)
{
	if (sel->type == SELECT_LIGHT)
	{
		if (sel->param & 1)
			sel->l->brightness += 0.1f;
		else
			sel->l->shadow_cast = 1;
	}
	else if (sel->type == SELECT_SPHERE)
		sel->sp->diam += 0.1f;
	else if (sel->type == SELECT_SQUARE)
		resize_square(sel->sq, get_square_side(sel->sq) + 0.1f);
	else if (sel->type == SELECT_CYLINDER)
	{
		if (sel->param & 1)
			sel->cy->diam += 0.1f;
		else
			sel->cy->height += 0.1f;
	}
}

void	decrement_object_param(t_select *sel)
{
	if (sel->type == SELECT_LIGHT)
	{
		if (sel->param & 1)
			sel->l->brightness -= 0.1f;
		else
			sel->l->shadow_cast = 0;
	}
	else if (sel->type == SELECT_SPHERE)
		sel->sp->diam -= 0.1f;
	else if (sel->type == SELECT_SQUARE)
		resize_square(sel->sq, get_square_side(sel->sq) - 0.1f);
	else if (sel->type == SELECT_CYLINDER)
	{
		if (sel->param & 1)
			sel->cy->diam -= 0.1f;
		else
			sel->cy->height -= 0.1f;
	}
}

void	key_cam(t_scene *scn, int key)
{
	if (key == KEY_CAM_NEXT)
		scn->cam_i += 1;
	if (key == KEY_CAM_PREV)
		scn->cam_i -= 1;
	if (scn->cam_i < 0)
		scn->cam_i += FT_BLEN(scn->cameras);
	if (scn->cam_i < 0)
		scn->cam_i = -scn->cam_i % FT_BLEN(scn->cameras);
	if (scn->cam_i >= FT_BLEN(scn->cameras))
		scn->cam_i = scn->cam_i % FT_BLEN(scn->cameras);
	if (scn->cam_i < 0)
		scn->cam_i = 0;
}

void	key_settings(t_scene *scn, int key)
{
	if (key == KEY_Z)
		scn->edit_mode = !scn->edit_mode;
	if (key == KEY_X)
		scn->shadow_off = !scn->shadow_off;
	if (key == KEY_F)
		select_object(scn, &scn->select);
	if (key == KEY_R)
		scn->edit_object = !scn->edit_object;
	if (key == KEY_P && scn->edit_object)
		scn->select.param += 1;
}

int		get_keypress(int key, t_rt *rt)
{
	t_scene		*scn;
	t_camera	*cam;

	scn = &rt->scenes[rt->scn_i];
	cam = &scn->cameras[scn->cam_i];
	if (scn->select.type && scn->edit_object)
		move_object(&scn->select, key);
	else
		movement_and_rotation(cam->pos, cam->xangle, key);
	if (key == KEY_U && scn->edit_object)
		decrement_object_param(&scn->select);
	if (key == KEY_O && scn->edit_object)
		increment_object_param(&scn->select);
	if (key == KEY_ESC)
		free_and_exit(rt);
	key_settings(scn, key);
	key_cam(scn, key);
	rt->need_redraw = 1;
	return (1);
}
