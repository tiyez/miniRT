/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:11:53 by jsandsla          #+#    #+#             */
/*   Updated: 2020/11/28 15:12:33 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <libft.h>

void	error_header(void)
{
	static	int	error_printed;
	if (!error_printed)
		ft_putstr("Error\n");
	error_printed = 1;
}

void	error(const char *msg)
{
	error_header();
	ft_putstr("- ");
	ft_putstr(msg);
	ft_putchar('\n');
}

void	error_num(const char *msg, int num)
{
	char	*substr;
	char	*ch;

	error_header();
	substr = ft_strdup(msg);
	if (substr)
	{
		ch = ft_strchr(substr, '%');
		if (ch)
		{
			*ch = 0;
			ft_putstr("- ");
			ft_putstr(substr);
			ft_putnbr(num);
			ft_putstr(ch + 1);
			ft_putchar('\n');
		}
		else
			ft_putstr(msg);
		free(substr);
	}
}

void	error_str(const char *msg, const char *str)
{
	char	*substr;
	char	*ch;

	error_header();
	substr = ft_strdup(msg);
	if (substr)
	{
		ch = ft_strchr(substr, '%');
		if (ch)
		{
			*ch = 0;
			ft_putstr("- ");
			ft_putstr(substr);
			ft_putstr(str);
			ft_putstr(ch + 1);
			ft_putchar('\n');
		}
		else
			ft_putstr(msg);
		free(substr);
	}
}

void	error_exit(const char *msg, t_rt *rt)
{
	error(msg);
	free_rt(rt);
	exit(EXIT_FAILURE);
}

