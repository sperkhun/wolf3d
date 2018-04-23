/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:01:23 by sperkhun          #+#    #+#             */
/*   Updated: 2018/03/05 14:01:24 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		drawmenu(t_mlx m)
{
	int i;

	i = 7;
	while (i++ < 14)
	{
		if (!m.tex[i].img)
		{
			perror("Error");
			exit(1);
		}
	}
	mlx_put_image_to_window(m.mlx, m.win, m.tex[7].img, 0, 0);
	if (m.menu == 1)
	{
		mlx_put_image_to_window(m.mlx, m.win, m.tex[8].img, 552, 350);
		mlx_put_image_to_window(m.mlx, m.win, m.tex[9].img, 552, 450);
	}
	else
	{
		mlx_put_image_to_window(m.mlx, m.win, m.tex[11].img, 552, 350);
		mlx_put_image_to_window(m.mlx, m.win, m.tex[12].img, 552, 450);
		if (m.ar == 4)
			mlx_put_image_to_window(m.mlx, m.win, m.tex[13].img, 552, 550);
	}
	mlx_put_image_to_window(m.mlx, m.win, m.tex[10].img, 520, m.sel);
}

static void	drawfloor(t_mlx *m, int x, int y)
{
	int		xt;
	int		yt;
	int		i1;
	int		i2;
	double	d;

	while (y < WIN_H)
	{
		d = (WIN_H / 2 * 1.1) / (y - WIN_H / 2) / cos(m->rays[x]);
		xt = (int)((m->n.x_p + d * cos(m->n.anf)) * m->tex[4].w) % m->tex[4].w;
		yt = (int)((m->n.y_p + d * sin(m->n.anf)) * m->tex[4].h) % m->tex[4].h;
		i1 = x * m->bpp + y * m->s_line;
		i2 = xt * m->tex[4].bpp + yt * m->tex[4].s_line;
		if (m->tex[4].img)
		{
			m->pxl_img[i1] = m->tex[4].pxl_img[i2];
			m->pxl_img[++i1] = m->tex[4].pxl_img[++i2];
			m->pxl_img[++i1] = m->tex[4].pxl_img[++i2];
		}
		y++;
	}
}

static void	drawceil(t_mlx *m, int x, int y)
{
	int		xt;
	int		yt;
	int		i1;
	int		i2;
	double	d;

	while (y >= 0)
	{
		d = (WIN_H / 2 * 1.1) / (WIN_H / 2 - y) / cos(m->rays[x]);
		xt = (int)((m->n.x_p + d * cos(m->n.anf)) * m->tex[5].w) % m->tex[5].w;
		yt = (int)((m->n.y_p + d * sin(m->n.anf)) * m->tex[5].h) % m->tex[5].h;
		i1 = x * m->bpp + y * m->s_line;
		i2 = xt * m->tex[5].bpp + yt * m->tex[5].s_line;
		if (m->tex[5].img)
		{
			m->pxl_img[i1] = m->tex[5].pxl_img[i2];
			m->pxl_img[++i1] = m->tex[5].pxl_img[++i2];
			m->pxl_img[++i1] = m->tex[5].pxl_img[++i2];
		}
		y--;
	}
}

static void	drawwall(t_mlx *m, int x, int y, int y2)
{
	int xt;
	int yt;
	int i1;
	int i2;
	int h;

	h = y2 - y;
	y < 0 ? y = 0 : 0;
	xt = m->g.w < m->v.w ? (int)(m->g.ax * m->tex[m->n.t].w) % m->tex[m->n.t].w\
		: (int)(m->v.ay * m->tex[m->n.t].w) % m->tex[m->n.t].w;
	while (y <= y2 && y < WIN_H)
	{
		yt = y * 256 - WIN_H * 128 + h * 128;
		yt = ((yt * m->tex[m->n.t].h) / h) / 256;
		if (yt >= 0 && yt < m->tex[m->n.t].h && xt < m->tex[m->n.t].w &&\
			xt >= 0 && m->tex[m->n.t].img)
		{
			i1 = x * m->bpp + y * m->s_line;
			i2 = xt * m->tex[m->n.t].bpp + yt * m->tex[m->n.t].s_line;
			m->pxl_img[i1] = m->tex[m->n.t].pxl_img[i2];
			m->pxl_img[++i1] = m->tex[m->n.t].pxl_img[++i2];
			m->pxl_img[++i1] = m->tex[m->n.t].pxl_img[++i2];
		}
		y++;
	}
}

void		draw(t_mlx *m, int s, int e)
{
	double	a;
	int		x;
	int		y;
	int		h;

	x = s;
	while (x <= e)
	{
		m->n.anf = m->n.pov + m->rays[x];
		if (m->n.anf < 0)
			m->n.anf += 2 * M_PI;
		else if (m->n.anf > 2 * M_PI)
			m->n.anf -= 2 * M_PI;
		vert(m->n, &m->v, m->map);
		gor(m->n, &m->g, m->map);
		a = m->g.w < m->v.w ? m->g.w : m->v.w;
		m->n.t = m->g.w < m->v.w ? m->g.t : m->v.t;
		a *= 0.45 * cos(m->rays[x]);
		h = WIN_H * 0.5 / a;
		y = (WIN_H - h) / 2;
		drawwall(m, x, y, h + y);
		drawceil(m, x, y);
		drawfloor(m, x, h + y);
		x++;
	}
}
