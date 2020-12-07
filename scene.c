/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:44:24 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 17:03:33 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mlx.h>

t_scene	*new_scene(t_rt *rt)
{
	t_scene	*scn;

	scn = FT_BNEW(rt->scenes);
	if (!scn)
		error_exit("cannot allocate memory for scene.", rt);
	scn->rt = rt;
	scn->width = 800;
	scn->height = 600;
	scn->ambient_ratio = 0.1f;
	ft_make_v3(1, 1, 1, scn->ambient);
	return (scn);
}

t_scene	*init_scene_img(t_scene *scn)
{
	scn->img.img = mlx_new_image(scn->rt->mlx, scn->width, scn->height);
	if (!scn->img.img)
		error_exit("cannot create mlx image.", scn->rt);
	scn->img.ptr = (unsigned char *)mlx_get_data_addr(scn->img.img,
		&scn->img.bpp, &scn->img.line_sz, &scn->img.endian);
	if (!scn->img.ptr)
		error_exit("mlx image buffer undefined.", scn->rt);
	scn->img.bpp /= 8;
	scn->img.width = scn->width;
	scn->img.height = scn->height;
	ft_memset(scn->img.ptr, 0, scn->img.line_sz * scn->height);
	scn->cam_i = 0;
	scn->fb.ptr = malloc(scn->width * scn->height * 3 * sizeof(float));
	scn->fb.width = scn->width;
	scn->fb.height = scn->height;
	scn->fb.chan = 3;
	scn->fb.line = scn->fb.chan * scn->width;
	return (scn);
}

void	scene_blit(t_scene *scn)
{
	int		iy;
	int		ix;
	t_byte	*imgptr;
	float	*fbptr;

	iy = 0;
	while (iy < scn->height)
	{
		ix = 0;
		while (ix < scn->width)
		{
			imgptr = scn->img.ptr + iy * scn->img.line_sz + ix * scn->img.bpp;
			fbptr = scn->fb.ptr + iy * scn->fb.line + ix * scn->fb.chan;
			tone_mapping(fbptr);
			linear_to_srgb(fbptr);
			*(unsigned int *)imgptr = MAKE_RGBV(fbptr);
			ix += 1;
		}
		iy += 1;
	}
}

void	scene_blit_bmp(t_scene *scn, unsigned char *img)
{
	int				x;
	int				y;
	float			*fbptr;
	unsigned int	color;

	y = 0;
	while (y < scn->height)
	{
		x = 0;
		while (x < scn->width)
		{
			fbptr = get_fbptr(scn, x, scn->height - y - 1);
			color = MAKE_BGRV(fbptr);
			img[0] = (color >> 16) & 0xFF;
			img[1] = (color >> 8) & 0xFF;
			img[2] = color & 0xFF;
			img += BMP_BPP;
			x += 1;
		}
		y += 1;
	}
}

void	make_scene_matricies(t_scene *scn, t_camera *cam)
{
	ft_perspective((float)scn->width / scn->height, 1000.f, cam->fov,
		scn->proj);
	ft_lookat_xangle(cam->pos, cam->xangle, scn->view);
	ft_mul_m4_to(scn->proj, scn->view, scn->vp);
	ft_inv_m4_to(scn->vp, scn->inv_vp);
}
