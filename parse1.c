/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:42:01 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 15:42:17 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int		parse_resolution(t_scene *scn, t_vs *vs)
{
	int		success;

	success = !!ft_vs_read_int_unsign(vs, &scn->width);
	success = success && !!ft_vs_read_int_unsign(vs, &scn->height);
	scn->width = FT_MIN(scn->width, 2560);
	scn->height = FT_MIN(scn->height, 1395);
	return (success);
}

int		parse_ambient(t_scene *scn, t_vs *vs)
{
	int		success;

	success = !!ft_vs_read_float(vs, &scn->ambient_ratio);
	success = success && parse_scene_line_color(vs, scn->ambient);
	return (success);
}

int		parse_camera(t_scene *scn, t_vs *vs)
{
	int			success;
	t_camera	*cam;
	t_v3		dir;

	cam = FT_BNEW(scn->cameras);
	success = !!cam;
	success = success && parse_scene_line_v3(vs, cam->pos);
	success = success && parse_scene_line_v3(vs, dir);
	success = success && !!ft_vs_read_float(vs, &cam->fov);
	ft_make_xangle_dir(dir, cam->xangle);
	return (success);
}

int		parse_light(t_scene *scn, t_vs *vs)
{
	int			success;
	t_light		*light;

	light = FT_BNEW(scn->lights);
	success = !!light;
	success = success && parse_scene_line_v3(vs, light->pos);
	success = success && !!ft_vs_read_float(vs, &light->brightness);
	success = success && parse_scene_line_color(vs, light->color);
	light->shadow_cast = 1;
	return (success);
}
