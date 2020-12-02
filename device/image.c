/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:29:15 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/26 18:58:37 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "device_private.h"
#include <mlx.h>

void	free_image(t_image *img)
{
	t_device	*dv;

	dv = img->dv;
	if (img->img && dv && dv->mlx)
		mlx_destroy_image(dv->mlx, img->img);
	img->dv = 0;
	img->img = 0;
	img->width = 0;
	img->height = 0;
	img->bpp = 0;
	img->ptr = 0;
}

int		create_image(t_device *dv, t_image *img, int width, int height)
{
	int	endian;

	img->img = 0;
	if (dv->mlx && (img->img = mlx_new_image(dv->mlx, width, height)))
	{
		img->dv = dv;
		if ((img->ptr = (unsigned char *)mlx_get_data_addr(img->img,
			&img->bpp, &img->line_sz, &endian)))
		{
			img->width = width;
			img->height = height;
		}
		else
			free_image(img);
	}
	return (!!img->img);
}

void	show_image(t_image *img, int x, int y)
{
	t_device	*dv;

	dv = img->dv;
	if (img->img && dv && dv->mlx && dv->winmlx)
		mlx_put_image_to_window(dv->mlx, dv->winmlx, img->img, x, y);
}
