/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:03:58 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 16:04:12 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int		ray_trace_lights(t_scene *scn, t_ray *r)
{
	int		i;
	int		last;
	t_light	*l;
	t_aabb	aabb;

	last = -1;
	i = 0;
	while (i < FT_BLEN(scn->lights))
	{
		l = &scn->lights[i];
		make_aabb_from_point(&aabb, l->pos);
		if (ft_aabb_ray_test(aabb.min, aabb.max, r))
		{
			last = i;
			r->data = l;
		}
		i += 1;
	}
	return (last);
}

void	ray_trace(t_scene *scn, t_ray *r)
{
	ray_trace_spheres(scn, r);
	ray_trace_planes(scn, r);
	ray_trace_squares(scn, r);
	ray_trace_triangles(scn, r);
	ray_trace_cylinders(scn, r);
}
