/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:15:04 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 17:02:23 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <libft.h>
#include <mlx.h>

void	free_scene(t_scene *scene)
{
	if (scene->img.img)
		mlx_destroy_image(scene->rt->mlx, scene->img.img);
	if (scene->fb.ptr)
		free(scene->fb.ptr);
	scene->img.img = 0;
	scene->fb.ptr = 0;
	FT_BFREE(scene->cameras);
	FT_BFREE(scene->lights);
	FT_BFREE(scene->spheres);
	FT_BFREE(scene->planes);
	FT_BFREE(scene->squares);
	FT_BFREE(scene->cylinders);
	FT_BFREE(scene->triangles);
}

void	free_rt(t_rt *rt)
{
	int	i;

	i = 0;
	while (i < FT_BLEN(rt->scenes))
	{
		free_scene(&rt->scenes[i]);
		i += 1;
	}
	FT_BFREE(rt->scenes);
	if (rt->win)
	{
		mlx_clear_window(rt->mlx, rt->win);
		mlx_destroy_window(rt->mlx, rt->win);
	}
	if (rt->mlx)
		free(rt->mlx);
	free(rt);
}
