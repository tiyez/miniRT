/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:14:19 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/02 14:34:25 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <libft.h>

typedef struct	s_camera
{
	t_v3	pos;
	float	fov;
	t_quat	rot;
	float	xrot;
	float	yrot;
}				t_camera;

typedef struct	s_light
{
	t_v3	pos;
	float	brightness;
	t_v3	color;
}				t_light;

typedef struct	s_material
{
	t_v3	albedo;
}				t_mat;

typedef struct	s_sphere
{
	t_v3	pos;
	float	diam;
	t_mat	mat;
}				t_sphere;

typedef struct	s_plane
{
	t_v3	pos;
	t_v3	normal;
	t_mat	mat;
}				t_plane;

typedef struct	s_square
{
	t_v3	pos[4];
	t_v3	normal;
	t_mat	mat;
}				t_square;

typedef struct	s_cylinder
{
	t_v3	pos;
	t_v3	normal;
	float	diam;
	float	height;
	t_mat	mat;
}				t_cylinder;

typedef struct	s_triangle
{
	t_v3	pos[3];
	t_mat	mat;
}				t_triangle;

typedef struct	s_img
{
	void	*img;
	t_byte	*ptr;
	int		width;
	int		height;
	int		bpp;
	int		line_sz;
	int		endian;
}				t_img;

typedef struct	s_framebuffer
{
	float	*ptr;
	int		width;
	int		height;
	int		chan;
	int		line;
}				t_fb;

typedef struct s_rt	t_rt;

typedef struct	s_scene
{
	t_rt		*rt;
	int			width;
	int			height;
	t_img		img;
	t_fb		fb;
	float		ambient_ratio;
	t_v3		ambient;
	int			camera_i;
	t_camera	*cameras;
	t_light		*lights;
	t_sphere	*spheres;
	t_plane		*planes;
	t_square	*squares;
	t_cylinder	*cylinders;
	t_triangle	*triangles;
}				t_scene;

struct			s_rt
{
	void	*mlx;
	void	*win;
	t_scene	*scenes;
	int		need_redraw;
};

# define MAKE_RGB(R, G, B) (((R) << 16) | ((G) << 8) | (B))
# define MAKE_ARGB(A, R, G, B) (MAKE_RGB(R, G, B) | ((A) << 24))
# define F_TO_C(F) (unsigned int)((F) * 255)
# define MAKE_RGBF(R, G, B) MAKE_RGB(F_TO_C(R), F_TO_C(G), F_TO_C(B))
# define MAKE_ARGBF(A, R, G, B) (MAKE_RGBF(R, G, B) | (F_TO_C(A) << 24))
# define MAKE_RGBV(V) MAKE_RGBF((V)[0], (V)[1], (V)[2])
# define MAKE_GRAY(G) MAKE_RGB(G, G, G)
# define MAKE_GRAYF(G) MAKE_RGBF(G, G, G)

/* error.c */
void			error_header(void);
void			error(const char *msg);
void			error_num(const char *msg, int num);
void			error_str(const char *msg, const char *str);
void			error_exit(const char *msg, t_rt *rt);

/* parse.c */
void			parse_scene_file(t_scene *scn, const char *fname);

/* free.c */
void			free_rt(t_rt *rt);
void			free_scene(t_scene *scene);

#endif
