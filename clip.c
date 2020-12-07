/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:49:13 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 15:49:44 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int		calc_cohen_sutherland(t_v4 point)
{
	int		value;

	value = !((point[0] / point[3]) > -1 || (point[3] + point[0]) > 0) << 0;
	value |= !((point[0] / point[3]) < 1 || (point[3] - point[0]) > 0) << 1;
	value |= !((point[1] / point[3]) > -1 || (point[3] + point[1]) > 0) << 2;
	value |= !((point[1] / point[3]) < 1 || (point[3] - point[1]) > 0) << 3;
	value |= !((point[2] / point[3]) > -1 || (point[3] + point[2]) > 0) << 4;
	value |= !((point[2] / point[3]) < -FT_EPSF || (point[3]) > FT_EPSF) << 5;
	return (value);
}

void	calc_boundary_coords(t_v4 point, float bc[6])
{
	bc[0] = point[3] + point[0];
	bc[1] = point[3] - point[0];
	bc[2] = point[3] + point[1];
	bc[3] = point[3] - point[1];
	bc[4] = point[3] + point[2];
	bc[5] = point[3] - point[2];
}

int		test_clip_plane(float bc[2][6], float t[2])
{
	int		i;
	float	hit;

	i = 0;
	while (i < 6)
	{
		if (bc[1][i] < 0)
		{
			hit = bc[0][i] / (bc[0][i] - bc[1][i]);
			t[1] = FT_MIN(t[1], hit);
		}
		else if (bc[0][i] < 0)
		{
			hit = bc[0][i] / (bc[0][i] - bc[1][i]);
			t[0] = FT_MAX(t[0], hit);
		}
		if (t[0] > t[1])
			return (0);
		i += 1;
	}
	return (1);
}

int		clip_line(t_v4 line[2])
{
	int		cohen[2];
	float	bc[2][6];
	float	t[2];
	t_v4	tmp;
	t_v4	dir;

	cohen[0] = calc_cohen_sutherland(line[0]);
	cohen[1] = calc_cohen_sutherland(line[1]);
	if (cohen[0] & cohen[1])
		return (0);
	if (!(cohen[0] | cohen[1]))
		return (1);
	calc_boundary_coords(line[0], bc[0]);
	calc_boundary_coords(line[1], bc[1]);
	t[0] = 0;
	t[1] = 1;
	if (!test_clip_plane(bc, t))
		return (0);
	ft_sub_v4(line[1], line[0], dir);
	ft_copy_v4(line[0], tmp);
	if (cohen[0])
		ft_mulvs_add_v4(dir, t[0], line[0], line[0]);
	if (cohen[1])
		ft_mulvs_add_v4(dir, t[1], tmp, line[1]);
	return (1);
}
