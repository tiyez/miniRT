/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:14:52 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 17:41:09 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

#define OFFSETOF(type, member) ((size_t)&((type *)0)->l)

void	select_object_hack(t_select *sel, int num, void *ptr, int type)
{
	sel->type = type;
	((void **)((unsigned char *)sel + OFFSETOF(t_select, l)))[num] = ptr;
}

void	select_object_2(t_scene *scn, t_select *select, t_ray *r)
{
	int		index;

	if ((index = ray_trace_triangles(scn, r)) >= 0)
	{
		select->type = SELECT_TRIANGLE;
		select->tr = &scn->triangles[index];
	}
	if ((index = ray_trace_cylinders(scn, r)) >= 0)
	{
		select->type = SELECT_CYLINDER;
		select->cy = &scn->cylinders[index];
	}
	if ((index = ray_trace_lights(scn, r)) >= 0)
	{
		select->type = SELECT_LIGHT;
		select->l = &scn->lights[index];
	}
}

void	select_object(t_scene *scn, t_select *select)
{
	t_ray	ray;
	t_v3	pos;
	int		index;

	ft_make_v3(0, 0, 0.9f, pos);
	ft_persp_mul_v3m4(scn->inv_vp, pos, 1, pos);
	ft_make_ray_point(scn->cameras[scn->cam_i].pos, pos, &ray);
	select->type = 0;
	if ((index = ray_trace_spheres(scn, &ray)) >= 0)
	{
		select->type = SELECT_SPHERE;
		select->sp = &scn->spheres[index];
	}
	if ((index = ray_trace_planes(scn, &ray)) >= 0)
	{
		select->type = SELECT_PLANE;
		select->pl = &scn->planes[index];
	}
	if ((index = ray_trace_squares(scn, &ray)) >= 0)
	{
		select->type = SELECT_SQUARE;
		select->sq = &scn->squares[index];
	}
	select_object_2(scn, select, &ray);
}

void	select_make_aabb(t_select *sel, t_aabb *b)
{
	if (sel->type == SELECT_LIGHT)
		make_aabb_from_point(b, sel->l->pos);
	else if (sel->type == SELECT_SPHERE)
		make_aabb_from_sphere(b, sel->sp);
	else if (sel->type == SELECT_PLANE)
		make_aabb_from_plane(b, sel->pl);
	else if (sel->type == SELECT_SQUARE)
		make_aabb_from_square(b, sel->sq);
	else if (sel->type == SELECT_CYLINDER)
		make_aabb_from_cylinder(b, sel->cy);
	else if (sel->type == SELECT_TRIANGLE)
		make_aabb_from_triangle(b, sel->tr);
}
