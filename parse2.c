/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:42:35 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 16:53:47 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		parse_sphere(t_scene *scn, t_vs *vs)
{
	int			success;
	t_sphere	*sphere;

	sphere = FT_BNEW(scn->spheres);
	success = !!sphere;
	success = success && parse_scene_line_v3(vs, sphere->pos);
	success = success && !!ft_vs_read_float(vs, &sphere->diam);
	success = success && parse_scene_line_color(vs, sphere->mat.albedo);
	return (success);
}

int		parse_plane(t_scene *scn, t_vs *vs)
{
	int			success;
	t_plane		*plane;

	plane = FT_BNEW(scn->planes);
	success = !!plane;
	success = success && parse_scene_line_v3(vs, plane->pos);
	success = success && parse_scene_line_v3(vs, plane->normal);
	success = success && parse_scene_line_color(vs, plane->mat.albedo);
	return (success);
}

int		parse_square(t_scene *scn, t_vs *vs)
{
	int			success;
	t_square	*square;
	t_v3		center;
	float		side;

	side = 0;
	square = FT_BNEW(scn->squares);
	success = !!square;
	success = success && parse_scene_line_v3(vs, center);
	success = success && parse_scene_line_v3(vs, square->normal);
	success = success && !!ft_vs_read_float(vs, &side);
	success = success && parse_scene_line_color(vs, square->mat.albedo);
	create_square(square, center, side, square->normal);
	return (success);
}

int		parse_cylinder(t_scene *scn, t_vs *vs)
{
	int			success;
	t_cylinder	*cylinder;

	cylinder = FT_BNEW(scn->cylinders);
	success = !!cylinder;
	success = success && parse_scene_line_v3(vs, cylinder->pos);
	success = success && parse_scene_line_v3(vs, cylinder->normal);
	success = success && !!ft_vs_read_float(vs, &cylinder->diam);
	success = success && !!ft_vs_read_float(vs, &cylinder->height);
	success = success && parse_scene_line_color(vs, cylinder->mat.albedo);
	return (success);
}

int		parse_triangle(t_scene *scn, t_vs *vs)
{
	int			success;
	t_triangle	*triangle;

	triangle = FT_BNEW(scn->triangles);
	success = !!triangle;
	success = success && parse_scene_line_v3(vs, triangle->pos[0]);
	success = success && parse_scene_line_v3(vs, triangle->pos[1]);
	success = success && parse_scene_line_v3(vs, triangle->pos[2]);
	success = success && parse_scene_line_color(vs, triangle->mat.albedo);
	return (success);
}
