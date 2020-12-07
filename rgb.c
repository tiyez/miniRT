/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:44:56 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 17:05:33 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>

/*
**	approximation ACES by Krzysztof Narkowicz
*/

void	tone_mapping(t_v3 color)
{
	color[0] *= 0.6f;
	color[1] *= 0.6f;
	color[2] *= 0.6f;
	color[0] = (color[0] * (2.51f * color[0] + 0.03f)) /
		(color[0] * (2.43f * color[0] + 0.59f) + 0.14f);
	color[1] = (color[1] * (2.51f * color[1] + 0.03f)) /
		(color[1] * (2.43f * color[1] + 0.59f) + 0.14f);
	color[2] = (color[2] * (2.51f * color[2] + 0.03f)) /
		(color[2] * (2.43f * color[2] + 0.59f) + 0.14f);
	color[0] = FT_CLAMP(color[0], 0, 1);
	color[1] = FT_CLAMP(color[1], 0, 1);
	color[2] = FT_CLAMP(color[2], 0, 1);
}

void	linear_to_srgb(t_v3 color)
{
	if (color[0] > 0.0031308f)
		color[0] = 1.055f * powf(color[0], (1 / 2.4f)) - 0.055f;
	else
		color[0] *= 12.92f;
	if (color[1] > 0.0031308f)
		color[1] = 1.055f * powf(color[1], (1 / 2.4f)) - 0.055f;
	else
		color[1] *= 12.92f;
	if (color[2] > 0.0031308f)
		color[2] = 1.055f * powf(color[2], (1 / 2.4f)) - 0.055f;
	else
		color[2] *= 12.92f;
}

void	put_pixel(t_scene *scn, int x, int y, t_v3 color)
{
	float	*fbptr;

	if (x >= 0 && x < scn->width && y >= 0 && y < scn->height)
	{
		fbptr = get_fbptr(scn, x, y);
		fbptr[0] = color[0];
		fbptr[1] = color[1];
		fbptr[2] = color[2];
	}
}

void	inverse_pixel(t_scene *scn, int x, int y)
{
	float	*fbptr;

	if (x >= 0 && x < scn->width && y >= 0 && y < scn->height)
	{
		fbptr = get_fbptr(scn, x, y);
		fbptr[0] = 1 - fbptr[0];
		fbptr[1] = 1 - fbptr[1];
		fbptr[2] = 1 - fbptr[2];
	}
}
