/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:47:41 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 17:03:20 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

float	*get_fbptr(t_scene *scn, int x, int y)
{
	float	*ptr;

	ptr = scn->fb.ptr;
	ptr += y * scn->fb.line;
	ptr += x * scn->fb.chan;
	return (ptr);
}

void	swap_int(int *l, int *r)
{
	int	temp;

	temp = *l;
	*l = *r;
	*r = temp;
}
