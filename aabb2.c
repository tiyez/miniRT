/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:39:09 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 16:39:17 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	make_aabb_from_plane(t_aabb *b, t_plane *pl)
{
	t_v3	onormal[2];
	t_v3	point[2];

	if (ft_epsf(ft_fabsf(ft_dot_v3(pl->normal, (t_v3){0, 0, 1})) - 1, FT_EPSF))
		ft_cross_v3_to((t_v3){0, 1, 0}, pl->normal, onormal[0]);
	else
		ft_cross_v3_to((t_v3){0, 0, 1}, pl->normal, onormal[0]);
	ft_cross_v3_to(pl->normal, onormal[0], onormal[1]);
	ft_mulvs_add_v3(onormal[0], 10.f, pl->pos, point[0]);
	ft_mulvs_add_v3(onormal[1], 10.f, point[0], point[0]);
	ft_mulvs_add_v3(onormal[0], -10.f, pl->pos, point[1]);
	ft_mulvs_add_v3(onormal[1], -10.f, point[1], point[1]);
	*b = make_aabb_from_4_points(point[0], point[1], pl->pos, pl->pos);
}

void	make_aabb_from_square(t_aabb *b, t_square *s)
{
	*b = make_aabb_from_4_points(s->pos[0], s->pos[1], s->pos[2], s->pos[3]);
}

void	make_aabb_from_cylinder(t_aabb *b, t_cylinder *c)
{
	t_v3	onormal[2];
	t_v3	point[2];

	if (ft_epsf(ft_fabsf(ft_dot_v3(c->normal, (t_v3){0, 0, 1})) - 1, FT_EPSF))
		ft_cross_v3_to((t_v3){0, 1, 0}, c->normal, onormal[0]);
	else
		ft_cross_v3_to((t_v3){0, 0, 1}, c->normal, onormal[0]);
	ft_cross_v3_to(c->normal, onormal[0], onormal[1]);
	ft_mulvs_add_v3(onormal[0], c->diam * 0.5f, c->pos, point[0]);
	ft_mulvs_add_v3(onormal[1], c->diam * 0.5f, point[0], point[0]);
	ft_mulvs_add_v3(c->normal, c->height * 0.5f, point[0], point[0]);
	ft_mulvs_add_v3(onormal[0], c->diam * -0.5f, c->pos, point[1]);
	ft_mulvs_add_v3(onormal[1], c->diam * -0.5f, point[1], point[1]);
	ft_mulvs_add_v3(c->normal, c->height * -0.5f, point[1], point[1]);
	*b = make_aabb_from_4_points(point[0], point[1], c->pos, c->pos);
}

void	draw_aabb(t_scene *scn, t_aabb *b)
{
	t_v3	up[4];
	t_v3	down[4];
	t_v3	dim;

	ft_sub_v3(b->max, b->min, dim);
	ft_mul_add_v3((t_v3){0, 1, 0}, dim, b->min, up[0]);
	ft_mul_add_v3((t_v3){0, 1, 1}, dim, b->min, up[1]);
	ft_mul_add_v3((t_v3){1, 1, 1}, dim, b->min, up[2]);
	ft_mul_add_v3((t_v3){1, 1, 0}, dim, b->min, up[3]);
	ft_mul_add_v3((t_v3){0, 0, 0}, dim, b->min, down[0]);
	ft_mul_add_v3((t_v3){0, 0, 1}, dim, b->min, down[1]);
	ft_mul_add_v3((t_v3){1, 0, 1}, dim, b->min, down[2]);
	ft_mul_add_v3((t_v3){1, 0, 0}, dim, b->min, down[3]);
	draw_line(scn, up[0], up[1]);
	draw_line(scn, up[1], up[2]);
	draw_line(scn, up[2], up[3]);
	draw_line(scn, up[3], up[0]);
	draw_line(scn, down[0], down[1]);
	draw_line(scn, down[1], down[2]);
	draw_line(scn, down[2], down[3]);
	draw_line(scn, down[3], down[0]);
	draw_line(scn, up[0], down[0]);
	draw_line(scn, up[1], down[1]);
	draw_line(scn, up[2], down[2]);
	draw_line(scn, up[3], down[3]);
}

void	draw_colored_aabb(t_scene *scn, t_aabb *b, t_v3 color)
{
	t_v3	up[4];
	t_v3	down[4];
	t_v3	dim;

	ft_sub_v3(b->max, b->min, dim);
	ft_mul_add_v3((t_v3){0, 1, 0}, dim, b->min, up[0]);
	ft_mul_add_v3((t_v3){0, 1, 1}, dim, b->min, up[1]);
	ft_mul_add_v3((t_v3){1, 1, 1}, dim, b->min, up[2]);
	ft_mul_add_v3((t_v3){1, 1, 0}, dim, b->min, up[3]);
	ft_mul_add_v3((t_v3){0, 0, 0}, dim, b->min, down[0]);
	ft_mul_add_v3((t_v3){0, 0, 1}, dim, b->min, down[1]);
	ft_mul_add_v3((t_v3){1, 0, 1}, dim, b->min, down[2]);
	ft_mul_add_v3((t_v3){1, 0, 0}, dim, b->min, down[3]);
	draw_colored_line(scn, up[0], up[1], color);
	draw_colored_line(scn, up[1], up[2], color);
	draw_colored_line(scn, up[2], up[3], color);
	draw_colored_line(scn, up[3], up[0], color);
	draw_colored_line(scn, down[0], down[1], color);
	draw_colored_line(scn, down[1], down[2], color);
	draw_colored_line(scn, down[2], down[3], color);
	draw_colored_line(scn, down[3], down[0], color);
	draw_colored_line(scn, up[0], down[0], color);
	draw_colored_line(scn, up[1], down[1], color);
	draw_colored_line(scn, up[2], down[2], color);
	draw_colored_line(scn, up[3], down[3], color);
}
