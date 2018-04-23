/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 13:56:51 by sperkhun          #+#    #+#             */
/*   Updated: 2018/03/27 13:56:52 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	new_game(t_thr *t)
{
	if (t->m.menu == 2)
	{
		t->m.sel == 450 ? t->m.a = 2 : 0;
		t->m.sel == 550 ? t->m.a = 3 : 0;
		t->m.menu = 0;
	}
	if (t->m.menu == 1 && t->m.sel == 350)
		t->m.menu = t->m.ar > 2 ? 2 : 0;
	if (t->m.menu == 0)
	{
		readmap(t->m.arg[t->m.a], &t->m);
		mlx_clear_window(t->m.mlx, t->m.win);
		draw_image(t);
	}
}

int			k2_hook(int key, t_thr *t)
{
	if (key == 53 || (t->m.menu == 1 && t->m.sel == 450 && key == 36))
		my_exit(t);
	if (!t->m.menu)
	{
		if (key == 126 || key == 13)
			t->m.n.up = !t->m.n.up;
		if (key == 125 || key == 1)
			t->m.n.down = !t->m.n.down;
		key == 124 || key == 2 ? t->m.n.right = !t->m.n.right : 0;
		key == 123 || key == 0 ? t->m.n.left = !t->m.n.left : 0;
	}
	return (0);
}

int			k1_hook(int key, t_thr *t)
{
	if (!t->m.menu)
		k2_hook(key, t);
	else
	{
		if (key == 36)
			new_game(t);
		if (key == 126 || key == 125)
		{
			if (t->m.menu == 1 || t->m.ar != 4)
				t->m.sel = t->m.sel == 350 ? 450 : 350;
			else if (t->m.menu == 2)
			{
				if (key == 126)
					t->m.sel = t->m.sel == 350 ? 550 : t->m.sel - 100;
				else
					t->m.sel = t->m.sel == 550 ? 350 : t->m.sel + 100;
			}
		}
	}
	return (0);
}

int			l_hook(t_thr *t)
{
	t->m.n.up ? moveup(&t->m) : 0;
	t->m.n.down ? movedown(&t->m) : 0;
	t->m.n.right || t->m.n.left ? turn(&t->m.n) : 0;
	if (!t->m.menu && t->m.map[(int)t->m.n.y_p][(int)t->m.n.x_p] == 'X')
	{
		t->m.a++;
		ft_arrdel(t->m.map, t->m.n.n_l);
		t->m.a < t->m.ar ? readmap(t->m.arg[t->m.a], &t->m) : 0;
		if (t->m.a == t->m.ar)
		{
			t->m.menu = 1;
			t->m.a = 1;
			t->m.n.up = 0;
			t->m.n.down = 0;
			t->m.n.left = 0;
			t->m.n.right = 0;
		}
	}
	if (t->m.n.right || t->m.n.left || t->m.n.up || t->m.n.down || t->m.menu)
	{
		mlx_clear_window(t->m.mlx, t->m.win);
		!t->m.menu ? draw_image(t) : drawmenu(t->m);
	}
	return (0);
}

int			exit_x(void *par)
{
	my_exit(par);
	return (0);
}
