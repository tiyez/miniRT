/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:02:34 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 16:03:15 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int		ray_trace_triangles(t_scene *scn, t_ray *r)
{
	int			i;
	int			last;
	t_triangle	*tr;

	i = 0;
	last = -1;
	while (i < FT_BLEN(scn->triangles))
	{
		tr = &scn->triangles[i];
		if (ft_triangle_ray_test(tr->pos, r))
		{
			last = i;
			r->data = &tr->mat;
		}
		i += 1;
	}
	return (last);
}

int		ray_trace_cylinders(t_scene *scn, t_ray *r)
{
	int			i;
	int			last;
	float		rhh[2];
	t_cylinder	*cy;

	i = 0;
	last = -1;
	while (i < FT_BLEN(scn->cylinders))
	{
		cy = &scn->cylinders[i];
		rhh[0] = cy->diam * 0.5f;
		rhh[1] = cy->height * 0.5f;
		if (ft_cylinder_ray_test(cy->pos, cy->normal, rhh, r))
		{
			last = i;
			r->data = &cy->mat;
		}
		i += 1;
	}
	return (last);
}

int		ray_trace_squares(t_scene *scn, t_ray *r)
{
	int			i;
	int			last;
	t_v3		tr2[3];
	t_square	*sq;
	void		*old_data;

	i = 0;
	last = -1;
	while (i < FT_BLEN(scn->squares))
	{
		old_data = r->data;
		sq = &scn->squares[i];
		if (!ft_triangle_ray_test(sq->pos, r))
		{
			ft_copy_v3(sq->pos[0], tr2[0]);
			ft_copy_v3(sq->pos[2], tr2[1]);
			ft_copy_v3(sq->pos[3], tr2[2]);
			r->data = ft_triangle_ray_test(tr2, r) ? &sq->mat : r->data;
		}
		else
			r->data = &sq->mat;
		last = old_data != r->data ? i : last;
		i += 1;
	}
	return (last);
}

int		ray_trace_planes(t_scene *scn, t_ray *r)
{
	int		i;
	int		last;
	t_plane	*pl;

	i = 0;
	last = -1;
	while (i < FT_BLEN(scn->planes))
	{
		pl = &scn->planes[i];
		if (ft_plane_ray_test(pl->pos, pl->normal, r))
		{
			last = i;
			r->data = &pl->mat;
		}
		i += 1;
	}
	return (last);
}

int		ray_trace_spheres(t_scene *scn, t_ray *r)
{
	int			i;
	int			last;
	t_sphere	*sp;

	last = -1;
	i = 0;
	while (i < FT_BLEN(scn->spheres))
	{
		sp = &scn->spheres[i];
		if (ft_sphere_ray_test(sp->pos, sp->diam / 2, r))
		{
			last = i;
			r->data = &sp->mat;
		}
		i += 1;
	}
	return (last);
}
