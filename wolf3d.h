/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 11:13:37 by sperkhun          #+#    #+#             */
/*   Updated: 2018/03/02 11:13:38 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H

# define WOLF3D_H

# include "libft.h"
# include <unistd.h>
# include <math.h>
# include "mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <SDL_mixer.h>

# define WIN_H 1000

# define WIN_W 1440

typedef struct		s_nb
{
	float			anf;
	float			x_p;
	float			y_p;
	float			pov;
	float			an;
	int				n_l;
	int				s_l;
	int				t;
	int				up;
	int				down;
	int				left;
	int				right;
}					t_nb;

typedef struct		s_tr
{
	float			xa;
	float			ya;
	float			ax;
	float			ay;
	float			w;
	int				px;
	int				py;
	int				t;
}					t_tr;

typedef struct		s_tex
{
	void			*img;
	char			*pxl_img;
	int				bpp;
	int				s_line;
	int				ed;
	int				w;
	int				h;
}					t_tex;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*pxl_img;
	int				bpp;
	int				s_line;
	int				ed;
	t_nb			n;
	t_tr			v;
	t_tr			g;
	t_tex			tex[14];
	float			rays[WIN_W];
	int				th;
	char			**map;
	Mix_Chunk		*step[6];
	Mix_Music		*music;
	int				i;
	int				menu;
	int				sel;
	char			**arg;
	int				a;
	int				ar;
}					t_mlx;

typedef struct		s_thr
{
	t_mlx			m;
	t_mlx			*mt;
	pthread_t		*thr;
}					t_thr;

void				opnwin(t_mlx *m);
void				crthr(t_thr *t);
int					k2_hook(int key, t_thr *m);
void				draw(t_mlx *m, int s, int e);
void				draw_image(t_thr *t);
int					exit_x(void *par);
int					l_hook(t_thr *t);
void				readmap(char *str, t_mlx *m);
void				drawmenu(t_mlx m);
int					k1_hook(int key, t_thr *t);
void				vert(t_nb n, t_tr *v, char **map);
void				gor(t_nb n, t_tr *g, char **map);
void				moveup(t_mlx *m);
void				movedown(t_mlx *m);
void				turn(t_nb *n);
void				inittable(float (*rays)[], float s);
void				setpr(t_mlx *m, char **argv);
void				initmusic(t_mlx *m);
void				checkmaps(t_mlx *m);
void				my_exit(t_thr *t);

#endif
