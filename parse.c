/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:10:13 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/02 14:34:02 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <get_next_line.h>
#include <unistd.h>
#include <fcntl.h>

int		parse_scene_line_v3(t_vs *vs, t_v3 v3)
{
	int		success;

	success = !!ft_vs_read_float(vs, &v3[0]);
	success = success && ft_vs_next_if(vs, ',');
	success = success && !!ft_vs_read_float(vs, &v3[1]);
	success = success && ft_vs_next_if(vs, ',');
	success = success && !!ft_vs_read_float(vs, &v3[2]);
	return (success);
}

int		parse_scene_line_color(t_vs *vs, t_v3 v3)
{
	int		rgb[3];
	int		success;

	success = !!ft_vs_read_int_unsign(vs, &rgb[0]);
	success = success && ft_vs_next_if(vs, ',');
	success = success && !!ft_vs_read_int_unsign(vs, &rgb[1]);
	success = success && ft_vs_next_if(vs, ',');
	success = success && !!ft_vs_read_int_unsign(vs, &rgb[2]);
	v3[0] = FT_CLAMP(rgb[0], 0, 255) / 255.f;
	v3[1] = FT_CLAMP(rgb[1], 0, 255) / 255.f;
	v3[2] = FT_CLAMP(rgb[2], 0, 255) / 255.f;
	return (success);
}

int		parse_scene_line(t_scene *scn, t_vs *vs)
{
	int		success;

	success = 1;
	ft_vs_skip_ws(vs);
	if (ft_vs_next_if_word(vs, "R"))
	{
		success = !!ft_vs_read_int_unsign(vs, &scn->width);
		success = success && !!ft_vs_read_int_unsign(vs, &scn->height);
	}
	else if (ft_vs_next_if_word(vs, "A"))
	{
		success = !!ft_vs_read_float(vs, &scn->ambient_ratio);
		success = success && parse_scene_line_color(vs, scn->ambient);
	}
	else if (ft_vs_next_if_word(vs, "c"))
	{
		t_camera	*cam;
		t_v3		dir;
		t_v3		euler;

		cam = FT_BNEW(scn->cameras);
		success = !!cam;
		success = success && parse_scene_line_v3(vs, cam->pos);
		success = success && parse_scene_line_v3(vs, dir);
		success = success && !!ft_vs_read_float(vs, &cam->fov);
		if (ft_dot_v3(dir, dir) < FT_EPSF)
			ft_make_v3(0, 0, -1, dir);
		ft_ext_normalize_v3(dir);
		ft_make_quat_dir(dir, (t_v3){0, 0, 1}, (t_v3){0, 1, 0}, cam->rot);
		ft_quat_to_euler(cam->rot, euler);
		cam->xrot = euler[2];
		cam->yrot = euler[1];
	}
	else if (ft_vs_next_if_word(vs, "l"))
	{
		t_light		*light;

		light = FT_BNEW(scn->lights);
		success = !!light;
		success = success && parse_scene_line_v3(vs, light->pos);
		success = success && !!ft_vs_read_float(vs, &light->brightness);
		success = success && parse_scene_line_color(vs, light->color);
	}
	else if (ft_vs_next_if_word(vs, "sp"))
	{
		t_sphere	*sphere;

		sphere = FT_BNEW(scn->spheres);
		success = !!sphere;
		success = success && parse_scene_line_v3(vs, sphere->pos);
		success = success && !!ft_vs_read_float(vs, &sphere->diam);
		success = success && parse_scene_line_color(vs, sphere->mat.albedo);
	}
	else if (ft_vs_next_if_word(vs, "pl"))
	{
		t_plane		*plane;

		plane = FT_BNEW(scn->planes);
		success = !!plane;
		success = success && parse_scene_line_v3(vs, plane->pos);
		success = success && parse_scene_line_v3(vs, plane->normal);
		success = success && parse_scene_line_color(vs, plane->mat.albedo);
	}
	else if (ft_vs_next_if_word(vs, "sq"))
	{
		t_square	*square;
		t_v3		center;
		float		side = 0;
		t_v3		ax[4];

		square = FT_BNEW(scn->squares);
		success = !!square;
		success = success && parse_scene_line_v3(vs, center);
		success = success && parse_scene_line_v3(vs, square->normal);
		success = success && !!ft_vs_read_float(vs, &side);
		success = success && parse_scene_line_color(vs, square->mat.albedo);
		ft_make_axis_dir(square->normal, ax[0], ax[1], ax[2]);
		ft_mulvs_add_v3(ax[0], side, center, square->pos[0]);
		ft_mulvs_add_v3(ax[1], side, square->pos[0], square->pos[0]);
		ft_mulvs_add_v3(ax[0], -side, center, square->pos[1]);
		ft_mulvs_add_v3(ax[1], side, square->pos[1], square->pos[1]);
		ft_mulvs_add_v3(ax[0], -side, center, square->pos[2]);
		ft_mulvs_add_v3(ax[1], -side, square->pos[2], square->pos[2]);
		ft_mulvs_add_v3(ax[0], side, center, square->pos[3]);
		ft_mulvs_add_v3(ax[1], -side, square->pos[3], square->pos[3]);
	}
	else if (ft_vs_next_if_word(vs, "cy"))
	{
		t_cylinder	*cylinder;

		cylinder = FT_BNEW(scn->cylinders);
		success = !!cylinder;
		success = success && parse_scene_line_v3(vs, cylinder->pos);
		success = success && parse_scene_line_v3(vs, cylinder->normal);
		success = success && !!ft_vs_read_float(vs, &cylinder->diam);
		success = success && !!ft_vs_read_float(vs, &cylinder->height);
		success = success && parse_scene_line_color(vs, cylinder->mat.albedo);
	}
	else if (ft_vs_next_if_word(vs, "tr"))
	{
		t_triangle	*triangle;

		triangle = FT_BNEW(scn->triangles);
		success = !!triangle;
		success = success && parse_scene_line_v3(vs, triangle->pos[0]);
		success = success && parse_scene_line_v3(vs, triangle->pos[1]);
		success = success && parse_scene_line_v3(vs, triangle->pos[2]);
		success = success && parse_scene_line_color(vs, triangle->mat.albedo);
	}
	return (success);
}

int		parse_scene_fd(t_scene *scn, int fd)
{
	char	*line;
	int		success;
	t_vs	vs;
	int		line_i;

	success = 1;
	line_i = 0;
	while (get_next_line(fd, &line) > 0 && success)
	{
		vs = ft_vs_create_str(line);
		success = !!parse_scene_line(scn, &vs);
		line_i += success;
		free(line);
	}
	if (line)
		vs = ft_vs_create_str(line);
	success = success && !!line && parse_scene_line(scn, &vs);
	line_i += success;
	if (!success)
		error_num("cannot parse .rt file at line %.", line_i + 1);
	if (line)
		free(line);
	else
		error_exit("get_next_line error occurred.", scn->rt);
	return (success);
}

void	parse_scene_file(t_scene *scn, const char *fname)
{
	int		success;
	int		fd;

	fd = open(fname, O_RDONLY);
	success = 0;
	if (fd >= 0)
	{
		success = parse_scene_fd(scn, fd);
		close(fd);
	}
	else
		error_str("cannot open '%' file.", fname);
	if (!success)
	{
		error_str("cannot parse '%' file.", fname);
		error_exit("parse_scene_file error occurred.", scn->rt);
	}
}
