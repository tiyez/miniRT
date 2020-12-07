/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:10:13 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 15:42:30 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <get_next_line.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

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
		success = parse_resolution(scn, vs);
	else if (ft_vs_next_if_word(vs, "A"))
		success = parse_ambient(scn, vs);
	else if (ft_vs_next_if_word(vs, "c"))
		success = parse_camera(scn, vs);
	else if (ft_vs_next_if_word(vs, "l"))
		success = parse_light(scn, vs);
	else if (ft_vs_next_if_word(vs, "sp"))
		success = parse_sphere(scn, vs);
	else if (ft_vs_next_if_word(vs, "pl"))
		success = parse_plane(scn, vs);
	else if (ft_vs_next_if_word(vs, "sq"))
		success = parse_square(scn, vs);
	else if (ft_vs_next_if_word(vs, "cy"))
		success = parse_cylinder(scn, vs);
	else if (ft_vs_next_if_word(vs, "tr"))
		success = parse_triangle(scn, vs);
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
