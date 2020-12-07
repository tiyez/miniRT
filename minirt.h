/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:14:19 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 17:56:28 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <libft.h>

typedef struct	s_camera
{
	t_v3	pos;
	float	fov;
	t_v4	xangle;
}				t_camera;

typedef struct	s_light
{
	t_v3	pos;
	float	brightness;
	t_v3	color;
	int		shadow_cast;
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

typedef struct	s_aabb
{
	t_v3	min;
	t_v3	max;
}				t_aabb;

# define SELECT_LIGHT 1
# define SELECT_SPHERE 2
# define SELECT_PLANE 3
# define SELECT_SQUARE 4
# define SELECT_CYLINDER 5
# define SELECT_TRIANGLE 6

typedef struct	s_select
{
	int			type;
	int			param;
	t_light		*l;
	t_sphere	*sp;
	t_plane		*pl;
	t_square	*sq;
	t_cylinder	*cy;
	t_triangle	*tr;
}				t_select;

typedef struct	s_scene
{
	t_rt		*rt;
	int			width;
	int			height;
	t_img		img;
	t_fb		fb;
	t_m4		proj;
	t_m4		view;
	t_m4		vp;
	t_m4		inv_vp;
	int			edit_mode;
	int			edit_object;
	int			shadow_off;
	t_select	select;
	float		ambient_ratio;
	t_v3		ambient;
	int			cam_i;
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
	int		scn_i;
	int		need_redraw;
};

typedef unsigned short	t_word;
typedef unsigned int	t_dword;
typedef signed int	t_long;

typedef t_word	t_bm_head[7];
typedef t_dword	t_bm_info[10];

# define BMP_BPP 3

# define MAKE_RGB(R, G, B) (((R) << 16) | ((G) << 8) | (B))
# define MAKE_ARGB(A, R, G, B) (MAKE_RGB(R, G, B) | ((A) << 24))
# define F_TO_C(F) (unsigned int)((F) * 255)
# define MAKE_RGBF(R, G, B) MAKE_RGB(F_TO_C(R), F_TO_C(G), F_TO_C(B))
# define MAKE_ARGBF(A, R, G, B) (MAKE_RGBF(R, G, B) | (F_TO_C(A) << 24))
# define MAKE_RGBV(V) MAKE_RGBF((V)[0], (V)[1], (V)[2])

# define MAKE_BGR(R, G, B) (((B) << 16) | ((G) << 8) | (R))
# define MAKE_BGRF(R, G, B) MAKE_BGR(F_TO_C(R), F_TO_C(G), F_TO_C(B))
# define MAKE_BGRV(V) MAKE_BGRF((V)[0], (V)[1], (V)[2])

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_Q 12
# define KEY_E 14

# define KEY_I 34
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37
# define KEY_U 32
# define KEY_O 31

# define KEY_Z 6
# define KEY_X 7
# define KEY_F 3
# define KEY_R 15
# define KEY_P 35

# define KEY_ESC 53

# define KEY_CAM_NEXT 30
# define KEY_CAM_PREV 33

void			error_header(void);
void			error(const char *msg);
void			error_num(const char *msg, int num);
void			error_str(const char *msg, const char *str);
void			error_exit(const char *msg, t_rt *rt);

int				parse_scene_line_v3(t_vs *vs, t_v3 v3);
int				parse_scene_line_color(t_vs *vs, t_v3 v3);
int				parse_resolution(t_scene *scn, t_vs *vs);
int				parse_ambient(t_scene *scn, t_vs *vs);
int				parse_camera(t_scene *scn, t_vs *vs);
int				parse_light(t_scene *scn, t_vs *vs);
int				parse_sphere(t_scene *scn, t_vs *vs);
int				parse_plane(t_scene *scn, t_vs *vs);
int				parse_square(t_scene *scn, t_vs *vs);
int				parse_cylinder(t_scene *scn, t_vs *vs);
int				parse_triangle(t_scene *scn, t_vs *vs);
int				parse_scene_line(t_scene *scn, t_vs *vs);
int				parse_scene_fd(t_scene *scn, int fd);

void			parse_scene_file(t_scene *scn, const char *fname);

void			tone_mapping(t_v3 color);
void			linear_to_srgb(t_v3 color);
void			put_pixel(t_scene *scn, int x, int y, t_v3 color);
void			inverse_pixel(t_scene *scn, int x, int y);

float			*get_fbptr(t_scene *scn, int x, int y);
void			swap_int(int *l, int *r);

void			draw_line_2d(t_scene *scn, int p0[2], int p1[2]);
void			draw_colored_line_2d(t_scene *s, int p0[2], int p1[2], t_v3 c);
void			draw_line(t_scene *scn, t_v3 start, t_v3 end);
void			draw_colored_line(t_scene *scn, t_v3 start, t_v3 end, t_v3 col);

int				calc_cohen_sutherland(t_v4 point);
void			calc_boundary_coords(t_v4 point, float bc[6]);
int				test_clip_plane(float bc[2][6], float t[2]);
int				clip_line(t_v4 line[2]);

int				is_in_shadow(t_scene *scn, t_light *l, t_v3 point);
void			calc_diffuse_color(t_light *l, t_v3 point, t_ray *r, t_v3 col);
void			calc_specular_color(t_light *l, t_v3 point, t_ray *r, t_v3 col);
void			calc_light_color(t_scene *scn, t_light *l, t_ray *r, t_v3 col);
void			calc_color(t_scene *scn, t_ray *r, t_mat *mat, t_v3 out);

int				ray_trace_triangles(t_scene *scn, t_ray *r);
int				ray_trace_cylinders(t_scene *scn, t_ray *r);
int				ray_trace_squares(t_scene *scn, t_ray *r);
int				ray_trace_planes(t_scene *scn, t_ray *r);
int				ray_trace_spheres(t_scene *scn, t_ray *r);

int				ray_trace_lights(t_scene *scn, t_ray *r);
void			ray_trace(t_scene *scn, t_ray *r);

t_scene			*new_scene(t_rt *rt);
t_scene			*init_scene_img(t_scene *scn);
void			scene_blit(t_scene *scn);
void			scene_blit_bmp(t_scene *scn, unsigned char *img);
void			make_scene_matricies(t_scene *scn, t_camera *cam);

void			error_close_exit(const char *msg, int fd, void *img, t_rt *rt);
void			fill_bmp_head(t_scene *scn, t_bm_head head);
void			fill_bmp_info(t_scene *scn, t_bm_info info);
void			save_scene_bmp(t_rt *rt, t_scene *scn);

void			create_square(t_square *sq, t_v3 center, float side, t_v3 n);
float			get_square_side(t_square *sq);
void			get_square_pos(t_square *sq, t_v3 pos);
void			resize_square(t_square *sq, float side);

void			select_object_hack(t_select *sel, int num, void *ptr, int type);
void			select_object(t_scene *scn, t_select *select);
void			select_make_aabb(t_select *sel, t_aabb *b);

void			render_to_framebuffer(t_scene *scn, t_camera *cam);
void			render_edit(t_scene *scn);
int				render_scene(t_rt *rt);

void			movement(t_v3 pos, t_v4 xangle, int key);
void			rotation(t_v4 xangle, int key);
void			movement_and_rotation(t_v3 pos, t_v4 xangle, int key);
void			movement_and_rotation_dir(t_v3 pos, t_v3 dir, int key);
void			move_object(t_select *sel, int key);

void			free_rt(t_rt *rt);
void			free_scene(t_scene *scene);

void			increment_object_param(t_select *sel);
void			decrement_object_param(t_select *sel);
void			key_cam(t_scene *scn, int key);
void			key_settings(t_scene *scn, int key);
int				get_keypress(int key, t_rt *rt);

t_aabb			make_aabb_from_4_points(t_v3 a, t_v3 b, t_v3 c, t_v3 d);
void			make_aabb_from_point(t_aabb *b, t_v3 point);
void			make_aabb_from_triangle(t_aabb *b, t_triangle *t);
void			make_aabb_from_sphere(t_aabb *b, t_sphere *s);
void			make_aabb_from_plane(t_aabb *b, t_plane *pl);
void			make_aabb_from_square(t_aabb *b, t_square *s);
void			make_aabb_from_cylinder(t_aabb *b, t_cylinder *c);
void			draw_aabb(t_scene *scn, t_aabb *b);
void			draw_colored_aabb(t_scene *scn, t_aabb *b, t_v3 color);

int				free_and_exit(t_rt *rt);

#endif
