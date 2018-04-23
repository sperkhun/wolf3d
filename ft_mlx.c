/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 18:13:46 by sperkhun          #+#    #+#             */
/*   Updated: 2018/02/03 18:13:47 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	opnwin(t_mlx *m)
{
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, WIN_W, WIN_H, "WOLF3D");
	if (!m->mlx || !m->win)
	{
		perror("Error");
		exit(1);
	}
}

void	draw_image(t_thr *t)
{
	if (!(t->m.img = mlx_new_image(t->m.mlx, WIN_W, WIN_H)))
	{
		perror("Error");
		exit(1);
	}
	t->m.pxl_img = mlx_get_data_addr(t->m.img, &(t->m.bpp), \
										&(t->m.s_line), &(t->m.ed));
	t->m.bpp /= 8;
	crthr(t);
	mlx_put_image_to_window(t->m.mlx, t->m.win, t->m.img, 0, 0);
	mlx_destroy_image(t->m.mlx, t->m.img);
}
