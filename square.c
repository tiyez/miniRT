/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:06:27 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 16:06:57 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	create_square(t_square *sq, t_v3 center, float side, t_v3 normal)
{
	t_v3	ax[3];
	t_v4	xangle;

	ft_make_xangle_dir(normal, xangle);
	ft_make_xangle_axis(xangle, ax[0], ax[1], ax[2]);
	ft_copy_v3(normal, sq->normal);
	ft_mulvs_add_v3(ax[0], side, center, sq->pos[0]);
	ft_mulvs_add_v3(ax[1], side, sq->pos[0], sq->pos[0]);
	ft_mulvs_add_v3(ax[0], -side, center, sq->pos[1]);
	ft_mulvs_add_v3(ax[1], side, sq->pos[1], sq->pos[1]);
	ft_mulvs_add_v3(ax[0], -side, center, sq->pos[2]);
	ft_mulvs_add_v3(ax[1], -side, sq->pos[2], sq->pos[2]);
	ft_mulvs_add_v3(ax[0], side, center, sq->pos[3]);
	ft_mulvs_add_v3(ax[1], -side, sq->pos[3], sq->pos[3]);
}

float	get_square_side(t_square *sq)
{
	t_v3	sub;

	ft_sub_v3(sq->pos[0], sq->pos[1], sub);
	return (ft_length_v3(sub) * 0.5f);
}

void	get_square_pos(t_square *sq, t_v3 pos)
{
	ft_lerp_v3(sq->pos[0], sq->pos[2], 0.5f, pos);
}

void	resize_square(t_square *sq, float side)
{
	t_v3	center;

	get_square_pos(sq, center);
	create_square(sq, center, side, sq->normal);
}
