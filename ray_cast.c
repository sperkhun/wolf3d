/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 18:07:25 by sperkhun          #+#    #+#             */
/*   Updated: 2018/03/26 18:07:27 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	vert(t_nb n, t_tr *v, char **map)
{
	v->px = n.x_p;
	n.anf >= M_PI * 1.5 || n.anf <= M_PI_2 ? v->px++ : v->px--;
	v->xa = n.anf >= M_PI * 1.5 || n.anf <= M_PI_2 ? 1 : -1;
	v->ya = n.anf >= M_PI * 1.5 || n.anf <= M_PI_2 ? tan(n.anf) : -tan(n.anf);
	v->ax = n.anf >= M_PI * 1.5 || n.anf <= M_PI_2 ? v->px : v->px + 1;
	v->t = n.anf >= M_PI * 1.5 || n.anf <= M_PI_2 ? 3 : 0;
	v->ay = n.y_p + (v->ax - n.x_p) * tan(n.anf);
	v->w = 10000;
	v->py = v->ay;
	while (v->py >= 0 && v->px >= 0 && v->py < n.n_l && v->px < n.s_l)
	{
		if (map[v->py][v->px] == '*' || map[v->py][v->px] == 'X')
		{
			if (map[v->py][v->px] == 'X')
				v->t = 6;
			v->w = (v->ax - n.x_p) / cos(n.anf);
			break ;
		}
		v->ax += v->xa;
		v->ay += v->ya;
		v->px += v->xa;
		v->py = v->ay;
	}
}

void	gor(t_nb n, t_tr *g, char **map)
{
	g->py = n.y_p;
	n.anf <= M_PI ? g->py++ : g->py--;
	g->xa = n.anf <= M_PI ? 1 / tan(n.anf) : -1 / tan(n.anf);
	g->ya = n.anf <= M_PI ? 1 : -1;
	g->ay = n.anf <= M_PI ? g->py : g->py + 1;
	g->t = n.anf <= M_PI ? 1 : 2;
	g->ax = n.x_p + (g->ay - n.y_p) / tan(n.anf);
	g->w = 10000;
	g->px = g->ax;
	while (g->py >= 0 && g->px >= 0 && g->py < n.n_l && g->px < n.s_l)
	{
		if (map[g->py][g->px] == '*' || map[g->py][g->px] == 'X')
		{
			if (map[g->py][g->px] == 'X')
				g->t = 6;
			g->w = (g->ay - n.y_p) / sin(n.anf);
			break ;
		}
		g->ax += g->xa;
		g->ay += g->ya;
		g->py += g->ya;
		g->px = g->ax;
	}
}
