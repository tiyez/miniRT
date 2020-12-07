/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:00:53 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 16:59:13 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>

int		is_in_shadow(t_scene *scn, t_light *l, t_v3 point)
{
	t_ray	rshadow;
	t_v3	shadowpoint;

	ft_sub_v3(point, l->pos, rshadow.dir);
	ft_ext_normalize_v3(rshadow.dir);
	ft_copy_v3(l->pos, rshadow.ori);
	rshadow.hit = INFINITY;
	ray_trace(scn, &rshadow);
	ft_mulvs_add_v3(rshadow.dir, rshadow.hit, rshadow.ori, shadowpoint);
	ft_sub_v3(shadowpoint, point, shadowpoint);
	return (ft_epsf(ft_dot_v3(shadowpoint, shadowpoint), 0.000001f));
}

void	calc_diffuse_color(t_light *l, t_v3 point, t_ray *r, t_v3 color)
{
	t_v3	light_dir;
	float	distance;
	float	diff;

	ft_sub_v3(l->pos, point, light_dir);
	distance = ft_dot_v3(light_dir, light_dir);
	ft_ext_normalize_v3(light_dir);
	diff = ft_dot_v3(r->hitnormal, light_dir) * l->brightness;
	diff = diff < 0 ? 0 : diff;
	diff /= distance;
	ft_mulvs_v3(l->color, diff, color);
}

void	calc_specular_color(t_light *l, t_v3 point, t_ray *r, t_v3 color)
{
	t_v3	view_dir;
	t_v3	reflect;
	t_v3	light_dir;
	float	dot;
	float	spec;

	ft_sub_v3(r->ori, point, view_dir);
	ft_ext_normalize_v3(view_dir);
	ft_sub_v3(point, l->pos, light_dir);
	ft_ext_normalize_v3(light_dir);
	ft_mulvs_v3(r->hitnormal, ft_dot_v3(light_dir, r->hitnormal) * 2, reflect);
	ft_sub_v3(light_dir, reflect, reflect);
	dot = ft_dot_v3(view_dir, reflect);
	spec = 0;
	if (dot > 0)
		spec = powf(dot, 8.f);
	ft_mulvs_v3(l->color, spec, color);
}

void	calc_light_color(t_scene *scn, t_light *l, t_ray *r, t_v3 color)
{
	t_v3	lcolor[2];
	t_v3	point;
	t_v3	ambient;

	ft_mulvs_v3(scn->ambient, scn->ambient_ratio, ambient);
	ft_mulvs_add_v3(r->dir, r->hit, r->ori, point);
	ft_make_v3(0, 0, 0, lcolor[0]);
	ft_make_v3(0, 0, 0, lcolor[1]);
	if (scn->shadow_off || (l->shadow_cast &&
		is_in_shadow(scn, l, point)))
	{
		calc_diffuse_color(l, point, r, lcolor[0]);
		calc_specular_color(l, point, r, lcolor[1]);
	}
	ft_add_v3(lcolor[0], lcolor[1], color);
	ft_add_v3(color, ambient, color);
}

void	calc_color(t_scene *scn, t_ray *r, t_mat *mat, t_v3 out)
{
	int		i;
	t_v3	color_sum;
	t_v3	color;

	i = 0;
	ft_make_v3(0, 0, 0, color_sum);
	ft_ext_normalize_v3(r->hitnormal);
	while (!scn->edit_mode && i < FT_BLEN(scn->lights))
	{
		calc_light_color(scn, &scn->lights[i], r, color);
		ft_mul_add_v3(color, mat->albedo, color_sum, color_sum);
		i += 1;
	}
	if (i)
		ft_divvs_v3(color_sum, i, out);
	else
		ft_copy_v3(mat->albedo, out);
}
