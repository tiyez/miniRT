/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:17:24 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/25 19:55:06 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <device.h>
#include <stdio.h>

int		loop(void *param)
{
	(void)param;
	return (1);
}

int		main()
{
	void	*dv;

	if ((dv = create_device()))
	{
		if (create_window(dv, 800, 600, "Hello world!"))
		{
			device_main_loop(dv, loop, 0);
		}
		free_device(dv);
		dv = 0;
	}
}
