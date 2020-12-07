/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsandsla <jsandsla@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:35:32 by jsandsla          #+#    #+#             */
/*   Updated: 2020/12/07 17:50:25 by jsandsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <unistd.h>
#include <fcntl.h>

void	error_close_exit(const char *msg, int fd, void *img, t_rt *rt)
{
	close(fd);
	free(img);
	error_exit(msg, rt);
}

void	fill_bmp_head(t_scene *scn, t_bm_head head)
{
	head[0] = 19778;
	*(t_dword *)&head[1] = scn->width * scn->height * BMP_BPP +
		sizeof(t_bm_head) + sizeof(t_bm_info);
	*(t_dword *)&head[5] = sizeof(t_bm_head) + sizeof(t_bm_info);
}

void	fill_bmp_info(t_scene *scn, t_bm_info info)
{
	info[0] = sizeof(t_bm_info);
	info[1] = scn->width;
	info[2] = scn->height;
	info[3] = 1 | (24 << 16);
	info[4] = 0;
	info[5] = 0;
	info[6] = 0;
	info[7] = 0;
	info[8] = 0;
	info[9] = 0;
}

void	save_scene_bmp(t_rt *rt, t_scene *scn)
{
	int				fd;
	unsigned char	*img;
	t_bm_head		head;
	t_bm_info		info;

	fd = open("save.bmp", O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		error_exit("cannot open 'save.bmp' for saving scene.", rt);
	img = malloc(scn->width * scn->height * BMP_BPP);
	if (!img)
		error_exit("malloc failure. trying to save the scene image.", rt);
	scene_blit_bmp(scn, img);
	fill_bmp_head(scn, head);
	fill_bmp_info(scn, info);
	if (write(fd, head, sizeof(t_bm_head)) < 0)
		error_close_exit("write failure (t_bm_head)", fd, img, rt);
	if (write(fd, info, sizeof(t_bm_info)) < 0)
		error_close_exit("write failure (t_bm_info)", fd, img, rt);
	if (write(fd, img, scn->width * scn->height * BMP_BPP) < 0)
		error_close_exit("write failure (bmp data)", fd, img, rt);
	free(img);
	close(fd);
}
