/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 12:18:28 by sperkhun          #+#    #+#             */
/*   Updated: 2018/03/27 12:18:29 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	moveup(t_mlx *m)
{
	float	vx;
	float	vy;
	float	x;
	float	y;

	vx = cos(m->n.pov);
	vy = sin(m->n.pov);
	x = m->n.x_p + 0.1 * vx;
	y = m->n.y_p + 0.1 * vy;
	if (m->n.pov <= M_PI)
		m->map[(int)(y + 0.3)][(int)x] != '*' ? m->n.y_p = y : 0;
	else
		m->map[(int)(y - 0.3)][(int)x] != '*' ? m->n.y_p = y : 0;
	if (m->n.pov <= M_PI_2 || m->n.pov >= M_PI * 1.5)
		m->map[(int)y][(int)(x + 0.3)] != '*' ? m->n.x_p = x : 0;
	else
		m->map[(int)y][(int)(x - 0.3)] != '*' ? m->n.x_p = x : 0;
	if (m->i == 0 || m->i == 5)
		Mix_PlayChannel(-1, m->step[m->i], 0);
	m->i = m->i < 5 ? m->i + 1 : 0;
}

void	movedown(t_mlx *m)
{
	float	vx;
	float	vy;
	float	x;
	float	y;

	vx = cos(m->n.pov);
	vy = sin(m->n.pov);
	x = m->n.x_p - 0.1 * vx;
	y = m->n.y_p - 0.1 * vy;
	if (m->n.pov <= M_PI)
		m->map[(int)(y - 0.3)][(int)x] != '*' ? m->n.y_p = y : 0;
	else
		m->map[(int)(y + 0.3)][(int)x] != '*' ? m->n.y_p = y : 0;
	if (m->n.pov <= M_PI_2 || m->n.pov >= M_PI * 1.5)
		m->map[(int)y][(int)(x - 0.3)] != '*' ? m->n.x_p = x : 0;
	else
		m->map[(int)y][(int)(x + 0.3)] != '*' ? m->n.x_p = x : 0;
	if (m->i == 0 || m->i == 5)
		Mix_PlayChannel(-1, m->step[m->i], 0);
	m->i = m->i < 5 ? m->i + 1 : 0;
}

void	turn(t_nb *n)
{
	if (n->right)
		n->pov += 3.0 * M_PI / 180.0;
	if (n->left)
		n->pov -= 3.0 * M_PI / 180.0;
	if (n->pov < 0)
		n->pov += 2 * M_PI;
	else if (n->pov > 2 * M_PI)
		n->pov -= 2 * M_PI;
}
