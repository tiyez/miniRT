/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:33:21 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 17:04:07 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>

void	render_to_framebuffer(t_scene *scn, t_camera *cam)
{
	float	step[2];
	t_ray	ray;
	int		iy;
	int		ix;
	t_v3	pos;

	step[0] = 2.f / scn->width;
	step[1] = 2.f / scn->height;
	ft_copy_v3(cam->pos, ray.ori);
	make_scene_matricies(scn, cam);
	iy = -1;
	while (++iy < scn->height)
	{
		ix = -1;
		while (++ix < scn->width)
		{
			ft_make_v3(-1 + step[0] * ix, -1 + step[1] * iy, 0.9f, pos);
			ft_persp_mul_v3m4(scn->inv_vp, pos, 1, pos);
			ft_make_ray_point(cam->pos, pos, &ray);
			ray_trace(scn, &ray);
			if (ray.hit < INFINITY)
				calc_color(scn, &ray, ray.data, get_fbptr(scn, ix, iy));
		}
	}
}

void	render_edit(t_scene *scn)
{
	t_aabb	b;
	int		i;

	if (scn->select.type)
	{
		select_make_aabb(&scn->select, &b);
		draw_aabb(scn, &b);
	}
	i = 0;
	while (i < FT_BLEN(scn->lights))
	{
		make_aabb_from_point(&b, scn->lights[i].pos);
		ft_subvs_v3(b.max, 0.1f, b.max);
		ft_addvs_v3(b.min, 0.1f, b.min);
		draw_colored_aabb(scn, &b, (t_v3){1, 1, 0});
		i += 1;
	}
}

int		render_scene(t_rt *rt)
{
	t_scene		*scn;
	t_camera	*cam;

	scn = rt->scn_i >= 0 && rt->scn_i < FT_BLEN(rt->scenes) ?
		&rt->scenes[rt->scn_i] : 0;
	cam = scn && scn->cam_i >= 0 && scn->cam_i < FT_BLEN(scn->cameras) ?
		&scn->cameras[scn->cam_i] : 0;
	if (cam)
		render_to_framebuffer(scn, cam);
	if (scn->edit_mode)
		render_edit(scn);
	return (!!cam);
}
