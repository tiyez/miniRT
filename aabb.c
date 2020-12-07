/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 17:46:45 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/05 20:32:37 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <libft.h>

t_aabb	make_aabb_from_4_points(t_v3 a, t_v3 b, t_v3 c, t_v3 d)
{
	t_aabb	aabb;

	ft_max_v3(a, b, aabb.max);
	ft_max_v3(c, aabb.max, aabb.max);
	ft_max_v3(d, aabb.max, aabb.max);
	ft_min_v3(a, b, aabb.min);
	ft_min_v3(c, aabb.min, aabb.min);
	ft_min_v3(d, aabb.min, aabb.min);
	ft_subvs_v3(aabb.min, 0.1f, aabb.min);
	ft_addvs_v3(aabb.max, 0.1f, aabb.max);
	return (aabb);
}

void	make_aabb_from_point(t_aabb *b, t_v3 point)
{
	t_v3	points[2];

	ft_addvs_v3(point, 0.1f, points[0]);
	ft_addvs_v3(point, -0.1f, points[1]);
	*b = make_aabb_from_4_points(points[0], points[1], point, point);
}

void	make_aabb_from_triangle(t_aabb *b, t_triangle *t)
{
	*b = make_aabb_from_4_points(t->pos[0], t->pos[1], t->pos[2], t->pos[0]);
}

void	make_aabb_from_sphere(t_aabb *b, t_sphere *s)
{
	t_v3	point[2];

	ft_addvs_v3(s->pos, s->diam * 0.5f, point[0]);
	ft_addvs_v3(s->pos, s->diam * -0.5f, point[1]);
	*b = make_aabb_from_4_points(s->pos, point[0], s->pos, point[1]);
}
