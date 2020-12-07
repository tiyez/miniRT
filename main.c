/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:17:24 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 17:05:06 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mlx.h>

int		loop(t_rt *rt)
{
	t_scene	*scn;

	scn = &rt->scenes[rt->scn_i];
	if (rt->need_redraw)
	{
		ft_memset(scn->fb.ptr, 0, scn->fb.line * scn->fb.height * 4);
		render_scene(rt);
		scene_blit(scn);
		mlx_put_image_to_window(rt->mlx, rt->win, scn->img.img, 0, 0);
		rt->need_redraw = 0;
	}
	return (1);
}

int		free_and_exit(t_rt *rt)
{
	free_rt(rt);
	exit(EXIT_SUCCESS);
	return (1);
}

void	run_rt(int argc, char *av[], t_rt *rt)
{
	t_scene	*scn;

	rt->mlx = mlx_init();
	scn = new_scene(rt);
	parse_scene_file(scn, av[1]);
	init_scene_img(scn);
	render_scene(rt);
	scene_blit(scn);
	if (argc == 3 && ft_strncmp(av[2], "--save", 6) == 0)
		save_scene_bmp(rt, &rt->scenes[rt->scn_i]);
	else
	{
		rt->win = mlx_new_window(rt->mlx, scn->width, scn->height, "miniRT");
		mlx_put_image_to_window(rt->mlx, rt->win, scn->img.img, 0, 0);
		mlx_hook(rt->win, 2, 0, get_keypress, rt);
		mlx_hook(rt->win, 17, 0, free_and_exit, rt);
		mlx_loop_hook(rt->mlx, loop, rt);
		mlx_loop(rt->mlx);
	}
}

int		main(int argc, char *av[])
{
	t_rt	*rt;

	rt = ft_calloc(1, sizeof(t_rt));
	if (!rt)
	{
		error("malloc failure.");
		exit(EXIT_FAILURE);
	}
	if (argc <= 1 || argc > 3 ||
		(argc == 3 && ft_strncmp(av[2], "--save", 6) != 0) ||
		ft_strlen(av[1]) < 3 ||
		ft_strncmp(av[1] + ft_strlen(av[1]) - 3, ".rt", 3) != 0)
	{
		error_str("invalid parameters. usage: % `scene.rt` [--save]", av[0]);
		free_rt(rt);
		exit(EXIT_FAILURE);
	}
	run_rt(argc, av, rt);
	free_rt(rt);
}
