/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 13:25:10 by sperkhun          #+#    #+#             */
/*   Updated: 2018/03/28 13:25:11 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		inittable(float (*rays)[], float s)
{
	int i;

	i = 0;
	while (i < WIN_W)
	{
		(*rays)[i] = atan(-s + 2 * i * s / (WIN_W - 1));
		i++;
	}
}

void		my_exit(t_thr *t)
{
	int i;

	i = 0;
	while (i < 14)
	{
		if (t->m.tex[i].img)
			mlx_destroy_image(t->m.mlx, t->m.tex[i].img);
		i++;
	}
	mlx_destroy_window(t->m.mlx, t->m.win);
	free(t->thr);
	free(t->mt);
	t->m.music ? Mix_FreeMusic(t->m.music) : 0;
	t->m.step[0] ? Mix_FreeChunk(t->m.step[0]) : 0;
	t->m.step[5] ? Mix_FreeChunk(t->m.step[5]) : 0;
	Mix_CloseAudio();
	exit(0);
}

void		checkmaps(t_mlx *m)
{
	int i;
	int a;

	i = 1;
	while (m->arg[i])
	{
		a = 0;
		readmap(m->arg[i], m);
		while (a < 7)
		{
			mlx_destroy_image(m->mlx, m->tex[a].img);
			m->tex[a].img = NULL;
			a++;
		}
		ft_arrdel(m->map, m->n.n_l);
		i++;
	}
}

void		setpr(t_mlx *m, char **argv)
{
	m->menu = 1;
	m->sel = 350;
	m->n.up = 0;
	m->n.down = 0;
	m->n.left = 0;
	m->n.right = 0;
	m->arg = argv;
	m->a = 1;
	m->n.an = tan(WIN_W / 2);
	m->tex[7].img = mlx_xpm_file_to_image(m->mlx, "resources/back.xpm",\
				&m->tex[7].w, &m->tex[7].h);
	m->tex[8].img = mlx_xpm_file_to_image(m->mlx, "resources/new_game.xpm",\
				&m->tex[8].w, &m->tex[8].h);
	m->tex[9].img = mlx_xpm_file_to_image(m->mlx, "resources/quite.xpm",\
				&m->tex[9].w, &m->tex[9].h);
	m->tex[10].img = mlx_xpm_file_to_image(m->mlx, "resources/arrow.xpm",\
				&m->tex[10].w, &m->tex[10].h);
	m->tex[11].img = mlx_xpm_file_to_image(m->mlx, "resources/level_1.xpm",\
				&m->tex[11].w, &m->tex[11].h);
	m->tex[12].img = mlx_xpm_file_to_image(m->mlx, "resources/level_2.xpm",\
				&m->tex[12].w, &m->tex[12].h);
	m->tex[13].img = mlx_xpm_file_to_image(m->mlx, "resources/level_3.xpm",\
				&m->tex[13].w, &m->tex[13].h);
}

void		initmusic(t_mlx *m)
{
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		return ;
	m->music = Mix_LoadMUS("resources/forest.ogg");
	Mix_PlayMusic(m->music, -1);
	m->step[0] = Mix_LoadWAV("resources/step1.ogg");
	m->step[5] = Mix_LoadWAV("resources/step2.ogg");
	m->i = 0;
}
