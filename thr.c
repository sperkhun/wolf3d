/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 15:23:58 by sperkhun          #+#    #+#             */
/*   Updated: 2018/02/16 15:24:01 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	*runthr(void *m)
{
	t_mlx	*d;
	int		s;
	int		e;
	int		i;

	d = (t_mlx*)m;
	i = WIN_W / 8;
	e = d->th * i + i - 1;
	s = e - i + 1;
	draw(d, s, e);
	return (NULL);
}

void		crthr(t_thr *t)
{
	int i;

	i = 0;
	while (i < 8)
	{
		t->m.th = i;
		t->mt[i] = t->m;
		if (pthread_create(&(t->thr[i]), NULL, runthr, &(t->mt[i])) != 0)
			exit(0);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		pthread_join(t->thr[i], NULL);
		i++;
	}
}
