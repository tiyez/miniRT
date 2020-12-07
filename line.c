/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:48:23 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 15:50:17 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	draw_line_2d(t_scene *scn, int p0[2], int p1[2])
{
	float	x[2];
	float	y[2];
	float	step;
	int		i;

	x[1] = (p1[0] - p0[0]);
	y[1] = (p1[1] - p0[1]);
	if (FT_ABS(x[1]) >= FT_ABS(y[1]))
		step = FT_ABS(x[1]);
	else
		step = FT_ABS(y[1]);
	x[1] /= step;
	y[1] /= step;
	x[0] = p0[0];
	y[0] = p0[1];
	i = 1;
	while (i <= step)
	{
		inverse_pixel(scn, x[0], y[0]);
		x[0] += x[1];
		y[0] += y[1];
		i += 1;
	}
}

void	draw_colored_line_2d(t_scene *scn, int p0[2], int p1[2], t_v3 color)
{
	float	x[2];
	float	y[2];
	float	step;
	int		i;

	x[1] = (p1[0] - p0[0]);
	y[1] = (p1[1] - p0[1]);
	if (FT_ABS(x[1]) >= FT_ABS(y[1]))
		step = FT_ABS(x[1]);
	else
		step = FT_ABS(y[1]);
	x[1] /= step;
	y[1] /= step;
	x[0] = p0[0];
	y[0] = p0[1];
	i = 1;
	while (i <= step)
	{
		put_pixel(scn, x[0], y[0], color);
		x[0] += x[1];
		y[0] += y[1];
		i += 1;
	}
}

void	draw_line(t_scene *scn, t_v3 start, t_v3 end)
{
	t_v4	projected[2];
	int		screen[2][2];

	projected[0][3] = ft_mul_v3m4(scn->vp, start, 1, projected[0]);
	projected[1][3] = ft_mul_v3m4(scn->vp, end, 1, projected[1]);
	if (clip_line(projected))
	{
		ft_divvs_v3(projected[0], projected[0][3], projected[0]);
		ft_divvs_v3(projected[1], projected[1][3], projected[1]);
		screen[0][0] = ((projected[0][0] + 1) * 0.5f) * scn->width;
		screen[0][1] = ((projected[0][1] + 1) * 0.5f) * scn->height;
		screen[1][0] = ((projected[1][0] + 1) * 0.5f) * scn->width;
		screen[1][1] = ((projected[1][1] + 1) * 0.5f) * scn->height;
		draw_line_2d(scn, screen[0], screen[1]);
	}
}

void	draw_colored_line(t_scene *scn, t_v3 start, t_v3 end, t_v3 color)
{
	t_v4	projected[2];
	int		screen[2][2];

	projected[0][3] = ft_mul_v3m4(scn->vp, start, 1, projected[0]);
	projected[1][3] = ft_mul_v3m4(scn->vp, end, 1, projected[1]);
	if (clip_line(projected))
	{
		ft_divvs_v3(projected[0], projected[0][3], projected[0]);
		ft_divvs_v3(projected[1], projected[1][3], projected[1]);
		screen[0][0] = ((projected[0][0] + 1) * 0.5f) * scn->width;
		screen[0][1] = ((projected[0][1] + 1) * 0.5f) * scn->height;
		screen[1][0] = ((projected[1][0] + 1) * 0.5f) * scn->width;
		screen[1][1] = ((projected[1][1] + 1) * 0.5f) * scn->height;
		draw_colored_line_2d(scn, screen[0], screen[1], color);
	}
}
