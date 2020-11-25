/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:17:24 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/25 16:13:35 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniLibX/mlx.h"

#define INVALID ((void *)0)

int		main()
{
	void	*mlx;
	void	*winmlx;

	if ((mlx = mlx_init()) != INVALID)
	{
		if ((winmlx = mlx_new_window(mlx, 800, 600, "Hello world")) != INVALID)
		{
			mlx_clear_window(mlx, winmlx);
			for (;;)
			{
				mlx_loop(mlx);
			}
		}
	}
}

