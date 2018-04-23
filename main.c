/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 11:19:34 by sperkhun          #+#    #+#             */
/*   Updated: 2018/03/02 11:19:35 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			main(int argc, char **argv)
{
	t_thr	t;

	if (argc > 4 || argc < 2)
	{
		ft_putendl("Wrong number of arguments");
		return (0);
	}
	t.thr = (pthread_t*)malloc(sizeof(pthread_t) * 8);
	t.mt = (t_mlx*)malloc(sizeof(t_mlx) * 8);
	t.m.ar = argc;
	opnwin(&t.m);
	setpr(&t.m, argv);
	checkmaps(&t.m);
	inittable(&t.m.rays, t.m.n.an);
	initmusic(&t.m);
	drawmenu(t.m);
	mlx_do_key_autorepeatoff(t.m.mlx);
	mlx_loop_hook(t.m.mlx, l_hook, &t);
	mlx_hook(t.m.win, 17, 5, exit_x, &t);
	mlx_hook(t.m.win, 2, 5, k2_hook, &t);
	mlx_key_hook(t.m.win, k1_hook, &t);
	mlx_loop(t.m.mlx);
	return (0);
}
