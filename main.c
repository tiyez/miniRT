/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:17:24 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/02 18:45:12 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <device.h>
#include <stdio.h>
#include <stdlib.h>
#include <minirt.h>
#include <mlx.h>
#include <get_next_line.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

void	print_v3(t_v3 v)
{
	ft_putchar('[');
	ft_putfloat(v[0]);
	ft_putstr(", ");
	ft_putfloat(v[1]);
	ft_putstr(", ");
	ft_putfloat(v[2]);
	ft_putchar(']');
}

void	print_v4(t_v4 v)
{
	ft_putchar('[');
	ft_putfloat(v[0]);
	ft_putstr(", ");
	ft_putfloat(v[1]);
	ft_putstr(", ");
	ft_putfloat(v[2]);
	ft_putstr(", ");
	ft_putfloat(v[3]);
	ft_putchar(']');
}

void	print_scene(t_scene *scn)
{
	int		i;

	i = 0;
	while (i < FT_BLEN(scn->cameras))
	{
		ft_putstr("camera: ");
		ft_putnbr(i);
		ft_putstr("\n\tpos: ");
		print_v3(scn->cameras[i].pos);
		ft_putstr("\n\trot: ");
		print_v3(scn->cameras[i].rot);
		ft_putstr("\n\tfov: ");
		ft_putfloat(scn->cameras[i].fov);
		ft_putchar('\n');
		i += 1;
	}
	i = 0;
	while (i < FT_BLEN(scn->lights))
	{
		ft_putstr("light: ");
		ft_putnbr(i);
		ft_putstr("\n\tpos: ");
		print_v3(scn->lights[i].pos);
		ft_putstr("\n\tbrightness: ");
		ft_putfloat(scn->lights[i].brightness);
		ft_putstr("\n\tcolor: ");
		print_v3(scn->lights[i].color);
		ft_putchar('\n');
		i += 1;
	}
	i = 0;
	while (i < FT_BLEN(scn->spheres))
	{
		ft_putstr("sphere: ");
		ft_putnbr(i);
		ft_putstr("\n\tpos: ");
		print_v3(scn->spheres[i].pos);
		ft_putstr("\n\tdiameter: ");
		ft_putfloat(scn->spheres[i].diam);
		ft_putstr("\n\tcolor: ");
		print_v3(scn->spheres[i].mat.albedo);
		ft_putchar('\n');
		i += 1;
	}
	i = 0;
	while (i < FT_BLEN(scn->planes))
	{
		ft_putstr("plane: ");
		ft_putnbr(i);
		ft_putstr("\n\tpos: ");
		print_v3(scn->planes[i].pos);
		ft_putstr("\n\tnormal: ");
		print_v3(scn->planes[i].normal);
		ft_putstr("\n\tcolor: ");
		print_v3(scn->planes[i].mat.albedo);
		ft_putchar('\n');
		i += 1;
	}
	i = 0;
	while (i < FT_BLEN(scn->squares))
	{
		ft_putstr("square: ");
		ft_putnbr(i);
		ft_putstr("\n\tpos 0: ");
		print_v3(scn->squares[i].pos[0]);
		ft_putstr("\n\tpos 1: ");
		print_v3(scn->squares[i].pos[1]);
		ft_putstr("\n\tpos 2: ");
		print_v3(scn->squares[i].pos[2]);
		ft_putstr("\n\tpos 3: ");
		print_v3(scn->squares[i].pos[3]);
		ft_putstr("\n\tcolor: ");
		print_v3(scn->squares[i].mat.albedo);
		ft_putchar('\n');
		i += 1;
	}
	i = 0;
	while (i < FT_BLEN(scn->cylinders))
	{
		ft_putstr("cylinder: ");
		ft_putnbr(i);
		ft_putstr("\n\tpos: ");
		print_v3(scn->cylinders[i].pos);
		ft_putstr("\n\tnormal: ");
		print_v3(scn->cylinders[i].normal);
		ft_putstr("\n\tdiameter: ");
		ft_putfloat(scn->cylinders[i].diam);
		ft_putstr("\n\theight: ");
		ft_putfloat(scn->cylinders[i].height);
		ft_putstr("\n\tcolor: ");
		print_v3(scn->cylinders[i].mat.albedo);
		ft_putchar('\n');
		i += 1;
	}
	i = 0;
	while (i < FT_BLEN(scn->triangles))
	{
		ft_putstr("triangle: ");
		ft_putnbr(i);
		ft_putstr("\n\tpos 0: ");
		print_v3(scn->triangles[i].pos[0]);
		ft_putstr("\n\tpos 1: ");
		print_v3(scn->triangles[i].pos[1]);
		ft_putstr("\n\tpos 2: ");
		print_v3(scn->triangles[i].pos[2]);
		ft_putstr("\n\tcolor: ");
		print_v3(scn->triangles[i].mat.albedo);
		ft_putchar('\n');
		i += 1;
	}
}

t_scene *new_scene(t_rt *rt)
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
	scn->camera_i = 0;
	scn->fb.ptr = malloc(scn->width * scn->height * 3 * sizeof(float));
	scn->fb.width = scn->width;
	scn->fb.height = scn->height;
	scn->fb.chan = 3;
	scn->fb.line = scn->fb.chan * scn->width;
	return (scn);
}

/*
** approximation ACES by Krzysztof Narkowicz
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

void	printf_m4(t_m4 m)
{
	printf("[%- 6.3g %- 6.3g %- 6.3g %- 6.3g]\n", m[0][0], m[1][0], m[2][0], m[3][0]);
	printf("[%- 6.3g %- 6.3g %- 6.3g %- 6.3g]\n", m[0][1], m[1][1], m[2][1], m[3][1]);
	printf("[%- 6.3g %- 6.3g %- 6.3g %- 6.3g]\n", m[0][2], m[1][2], m[2][2], m[3][2]);
	printf("[%- 6.3g %- 6.3g %- 6.3g %- 6.3g]\n", m[0][3], m[1][3], m[2][3], m[3][3]);
}

void	printf_v3(const char *msg, t_v3 v)
{
	printf("%s[%- 6.3g %- 6.3g %- 6.3g]\n", msg, v[0], v[1], v[2]);
}

void	printf_v4(const char *msg, t_v4 v)
{
	printf("%s[%- 6.3g %- 6.3g %- 6.3g %- 6.3g]\n", msg, v[0], v[1], v[2], v[3]);
}

float	*get_fbptr(t_scene *scn, int x, int y)
{
	float	*ptr = scn->fb.ptr;

	ptr += y * scn->fb.line;
	ptr += x * scn->fb.chan;
	return (ptr);
}

void	calc_color(t_scene *scn, t_ray *r, t_mat *mat, t_v3 out)
{
#if 0
	(void)scn, (void)r;
	out[0] = mat->albedo[0];
	out[1] = mat->albedo[1];
	out[2] = mat->albedo[2];
#else
	int		i = 0;
	t_v3	color_sum;
	t_v3	lcolor[3];
	t_v3	point;

	ft_make_v3(0, 0, 0, color_sum);
	ft_mulvs_add_v3(r->dir, r->hit, r->ori, point);
	ft_ext_normalize_v3(r->hitnormal);
	while (i < FT_BLEN(scn->lights))
	{
		t_light	*l = &scn->lights[i];

		ft_mulvs_v3(scn->ambient, scn->ambient_ratio, lcolor[0]);
		ft_mul_v3(l->color, lcolor[0], lcolor[0]);
//		ft_mul_v3(mat->albedo, lcolor[0], lcolor[0]);

		t_v3	light_dir;
		ft_sub_v3(l->pos, point, light_dir);
		float	distance = ft_dot_v3(light_dir, light_dir);
		ft_ext_normalize_v3(light_dir);
		float	diff = ft_dot_v3(r->hitnormal, light_dir) * l->brightness;
		diff = diff < 0 ? 0 : diff;
		diff /= distance;
		ft_mulvs_v3(l->color, diff, lcolor[1]);

		t_v3	view_dir;
		t_v3	reflect;
		float	specular = 0.5;
		ft_sub_v3(r->ori, point, view_dir);
		ft_ext_normalize_v3(view_dir);
		ft_subsv_v3(0, light_dir, light_dir);
		ft_mulvs_v3(r->hitnormal, ft_dot_v3(light_dir, r->hitnormal) * 2, reflect);
		ft_sub_v3(light_dir, reflect, reflect);
		float	dot = ft_dot_v3(view_dir, reflect);
		float	spec;
		if (dot <= 0)
			spec = 0;
		else
			spec = powf(dot, 16);
		ft_mulvs_v3(l->color, specular * spec, lcolor[2]);

		ft_add_v3(lcolor[0], lcolor[1], lcolor[0]);
		ft_add_v3(lcolor[0], lcolor[2], lcolor[0]);
		ft_mul_add_v3(lcolor[0], mat->albedo, color_sum, color_sum);

#if 0
		float dot = ft_dot_v3(light_dir, light_dir);
		float	intensity;
		if (!ft_epsf(dot, FT_EPSF))
			intensity = l->brightness / dot;
		else
			intensity = INFINITY;
		ft_mulvs_v3(l->color, intensity, lcolor[1]);
		ft_mul_v3(lcolor[1], mat->albedo, lcolor[1]);
#endif

//		ft_add_v3(color_sum, lcolor[0], color_sum);
//		ft_add_v3(color_sum, lcolor[1], color_sum);
		i += 1;
	}
	if (i)
		ft_divvs_v3(color_sum, i, out);
	else
		ft_copy_v3(mat->albedo, out);
#endif
}

int		render_scene(t_scene *scn, int cam_i)
{
	t_camera	*cam;
	t_m4		proj;
	t_m4		view;
	t_m4		vp;
	t_m4		inv_vp;
	t_v3		pos;

	cam = cam_i >= 0 && cam_i < FT_BLEN(scn->cameras) ?
		&scn->cameras[cam_i] : 0;
	if (cam)
	{
		ft_perspective((float)scn->width / scn->height, 1000.f, cam->fov, proj);
		ft_lookat_quat(cam->pos, cam->rot, view);
		ft_mul_m4_to(proj, view, vp);
		ft_inv_m4_to(vp, inv_vp);

		ft_make_v3(-1, -1, 0.9f, pos);
		float w = ft_mul_v3m4(inv_vp, pos, 1, pos);
		printf("proj:\n");
		printf_m4(proj);
		printf("view:\n");
		printf_m4(view);
		printf("vp:\n");
		printf_m4(vp);
		printf("inv_vp:\n");
		printf_m4(inv_vp);
		printf("pos: [%- 6.3g %- 6.3g %- 6.3g] %- 6.3g\n", pos[0], pos[1], pos[2], w);
		ft_divvs_v3(pos, w, pos);
		printf("pos: [%- 6.3g %- 6.3g %- 6.3g]\n", pos[0], pos[1], pos[2]);

		float	stepx = 2.f / scn->width;
		float	stepy = 2.f / scn->height;
		t_ray	ray;
		float	thit_min;
		ft_copy_v3(cam->pos, ray.ori);

		printf("width: %d\nheight: %d\nline_sz: %d\nbpp: %d\nwidth * bpp: %d\n", scn->img.width, scn->img.height, scn->img.line_sz, scn->img.bpp, scn->img.bpp * scn->img.width);

		int iy = 0;
		while (iy < scn->height)
		{
			int ix = 0;
			while (ix < scn->width)
			{
				ft_make_v3(-1 + stepx * ix, 1 - stepy * iy, 0.9f, pos);
				ft_persp_mul_v3m4(inv_vp, pos, 1, pos);
				ft_sub_v3(pos, ray.ori, ray.dir);
				ft_ext_normalize_v3(ray.dir);
				thit_min = INFINITY;

				int i = 0;
				while (i < FT_BLEN(scn->triangles))
				{
					t_triangle	*tr = &scn->triangles[i];
					if (ft_triangle_ray_test(tr->pos, &ray) && ray.hit < thit_min)
					{
						calc_color(scn, &ray, &tr->mat, get_fbptr(scn, ix, iy));
						thit_min = ray.hit;
					}
					i += 1;
				}
				i = 0;
				while (i < FT_BLEN(scn->spheres))
				{
					t_sphere	*sp = &scn->spheres[i];
					if (ft_sphere_ray_test(sp->pos, sp->diam / 2, &ray) && ray.hit < thit_min)
					{
						calc_color(scn, &ray, &sp->mat, get_fbptr(scn, ix, iy));
						thit_min = ray.hit;
					}
					i += 1;
				}
				i = 0;
				while (i < FT_BLEN(scn->planes))
				{
					t_plane	*pl = &scn->planes[i];
					if (ft_plane_ray_test(pl->pos, pl->normal, &ray) && ray.hit < thit_min)
					{
						calc_color(scn, &ray, &pl->mat, get_fbptr(scn, ix, iy));
						thit_min = ray.hit;
					}
					i += 1;
				}
				i = 0;
				while (i < FT_BLEN(scn->squares))
				{
					t_square	*sq = &scn->squares[i];
					t_v3		tr2[3];

					ft_copy_v3(sq->pos[0], tr2[0]);
					ft_copy_v3(sq->pos[2], tr2[1]);
					ft_copy_v3(sq->pos[3], tr2[2]);
					if ((ft_triangle_ray_test(sq->pos, &ray) ||
						 ft_triangle_ray_test(tr2, &ray)) && ray.hit < thit_min)
					{
						calc_color(scn, &ray, &sq->mat, get_fbptr(scn, ix, iy));
						thit_min = ray.hit;
					}
					i += 1;
				}
				i = 0;
				while (i < FT_BLEN(scn->cylinders))
				{
					t_cylinder	*cy = &scn->cylinders[i];
					float		rhh[2];

					rhh[0] = cy->diam * 0.5f;
					rhh[1] = cy->height * 0.5f;
					if (ft_cylinder_ray_test(cy->pos, cy->normal, rhh, &ray) && ray.hit < thit_min)
					{
						calc_color(scn, &ray, &cy->mat, get_fbptr(scn, ix, iy));
						thit_min = ray.hit;
					}
					i += 1;
				}
				ix += 1;
			}
			iy += 1;
		}

	}
	return (!!cam);
}

int		loop(t_rt *rt)
{
	t_scene	*scn = &rt->scenes[0];
	if (rt->need_redraw)
	{
		ft_memset(scn->fb.ptr, 0, scn->fb.line * scn->fb.height * sizeof(float));
		render_scene(scn, 0);
		scene_blit(scn);
		mlx_put_image_to_window(rt->mlx, rt->win, scn->img.img, 0, 0);
		rt->need_redraw = 0;
	}
	return (1);
}

#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_W 13
#define KEY_Q 12
#define KEY_E 14

#define KEY_I 34
#define KEY_J 38
#define KEY_K 40
#define KEY_L 37

int		euler_to_quat(float xrot, float yrot, t_quat out)
{
	t_quat q[2];
	t_v3 up = {0,1,0}, right = {1,0,0};

	ft_make_quat_axis(right, xrot, q[0]);
	ft_make_quat_axis(up, yrot, q[1]);
	ft_identity_quat(out);
	ft_mul_quat(out, q[0], out);
	ft_mul_quat(out, q[1], out);
	return (1);
}

int		quat_to_axis(t_quat quat, t_v3 right, t_v3 up, t_v3 forward)
{
	ft_make_v3(0, 0, 1, forward);
	ft_rotate_qv3(forward, quat, forward);
	ft_ext_normalize_v3(forward);
	ft_make_v3(0, 1, 0, up);
	ft_cross_v3_to(forward, up, right);
	ft_cross_v3_to(right, forward, up);
	return (1);
}

int		get_keypress(int key, t_rt *rt)
{
	t_scene		*scn = &rt->scenes[0];
	t_camera	*cam = &scn->cameras[0];
	t_v3		ax[3];

	quat_to_axis(cam->rot, ax[0], ax[1], ax[2]);
	ft_ext_normalize_v3(ax[0]);
	ft_ext_normalize_v3(ax[1]);
	ft_ext_normalize_v3(ax[2]);
	if (key == KEY_A)
		ft_mulvs_add_v3(ax[0],  0.1f, cam->pos, cam->pos);
	if (key == KEY_D)
		ft_mulvs_add_v3(ax[0], -0.1f, cam->pos, cam->pos);
	if (key == KEY_W)
		ft_mulvs_add_v3(ax[2], -0.1f, cam->pos, cam->pos);
	if (key == KEY_S)
		ft_mulvs_add_v3(ax[2],  0.1f, cam->pos, cam->pos);
	if (key == KEY_Q)
		ft_mulvs_add_v3(ax[1], -0.1f, cam->pos, cam->pos);
	if (key == KEY_E)
		ft_mulvs_add_v3(ax[1],  0.1f, cam->pos, cam->pos);
	if (key == KEY_I)
		cam->xrot -= FT_RAD(10);
	if (key == KEY_K)
		cam->xrot += FT_RAD(10);
	if (key == KEY_J)
		cam->yrot -= FT_RAD(10);
	if (key == KEY_L)
		cam->yrot += FT_RAD(10);
	euler_to_quat(cam->xrot, cam->yrot, cam->rot);
	ft_normalize_quat(cam->rot);
	rt->need_redraw = 1;
	printf("key: %d\n", key);
	return (1);
}

int		free_and_exit(t_rt *rt)
{
	free_rt(rt);
	exit(EXIT_SUCCESS);
	return (1);
}

int		main(int argc, char *av[])
{
	t_rt	*rt;
	t_scene	*scn;
	(void)argc, (void)av;

	{
		t_quat	q;
		t_v3	p = {1, 0, 0};

		ft_make_quat_axis((t_v3){0, 1, 0}, FT_RAD(90), q);
		printf_v3("p: ", p);
		printf_v4("q: ", q);
		ft_rotate_qv3(p, q, p);
		printf_v3("p: ", p);
	}

	rt = ft_calloc(1, sizeof(t_rt));
	rt->mlx = mlx_init();
	scn = new_scene(rt);
	parse_scene_file(scn, "test.rt");
	init_scene_img(scn);
	render_scene(scn, 0);
	scene_blit(scn);
	//print_scene(scn);
	rt->win = mlx_new_window(rt->mlx, scn->width, scn->height, "miniRT");
	mlx_put_image_to_window(rt->mlx, rt->win, scn->img.img, 0, 0);

	mlx_hook(rt->win, 2, 0, get_keypress, rt);
//	mlx_hook(rt->win, 3, 0, get_keypress, rt);
//	mlx_hook(rt->win_ptr, 4, 0, mouse_press, rt);
//	mlx_hook(rt->win_ptr, 5, 0, mouse_release, rt);
//	mlx_hook(rt->win_ptr, 6, 0, get_mouse_pos, rt);
	mlx_hook(rt->win, 17, 0, free_and_exit, rt);

	mlx_loop_hook(rt->mlx, loop, rt);

	mlx_loop(rt->mlx);
	free_rt(rt);
}
