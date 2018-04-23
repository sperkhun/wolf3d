/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 18:28:24 by sperkhun          #+#    #+#             */
/*   Updated: 2018/03/23 18:28:25 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	maper(char *str)
{
	ft_putstr("Wrong map named: ");
	ft_putendl(str);
	exit(0);
}

static void	inittex(t_mlx *m, int fd, char *str)
{
	int		i;
	char	*line;

	i = 0;
	while (i < 7)
	{
		if (get_next_line(fd, &line) < 0)
			maper(str);
		if (!(m->tex[i].img = mlx_xpm_file_to_image(m->mlx, line,\
			&m->tex[i].w, &m->tex[i].h)))
			maper(str);
		m->tex[i].pxl_img = mlx_get_data_addr(m->tex[i].img,\
			&(m->tex[i].bpp), &(m->tex[i].s_line), &(m->tex[i].ed));
		m->tex[i].bpp /= 8;
		ft_strdel(&line);
		i++;
	}
}

static int	validdot(char c, t_nb *n, int i, int j)
{
	if (c != '*' && c != 'v' && c != '^' && c != '>' &&\
			c != '<' && c != ' ' && c != 'X')
		return (0);
	else if (c != '*' && c != ' ' && c != 'X')
	{
		n->x_p = j + 0.5;
		n->y_p = i + 0.5;
		c == 'v' ? n->pov = M_PI_2 : 0;
		c == '^' ? n->pov = M_PI * 1.5 : 0;
		c == '<' ? n->pov = M_PI : 0;
		c == '>' ? n->pov = 0 : 0;
	}
	return (1);
}

static void	validmap(t_mlx *m, char *str)
{
	int i;
	int j;

	i = 0;
	m->n.x_p = 0;
	m->n.y_p = 0;
	while (i < m->n.n_l)
	{
		j = 0;
		while (j < m->n.s_l)
		{
			(i == 0 || i == m->n.n_l - 1) && m->map[i][j] != '*' &&\
					m->map[i][j] != 'X' ? maper(str) : 0;
			(j == 0 || j == m->n.s_l - 1) && m->map[i][j] != '*' &&\
					m->map[i][j] != 'X' ? maper(str) : 0;
			!validdot(m->map[i][j], &m->n, i, j) ? maper(str) : 0;
			j++;
		}
		i++;
	}
	m->n.x_p == 0 ? maper(str) : 0;
}

void		readmap(char *str, t_mlx *m)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(str, O_RDONLY);
	inittex(m, fd, str);
	get_next_line(fd, &line) < 0 ? maper(str) : 0;
	(m->n.n_l = ft_atoi(line)) < 3 ? maper(str) : 0;
	ft_strdel(&line);
	get_next_line(fd, &line) < 0 ? maper(str) : 0;
	(m->n.s_l = ft_atoi(line)) < 3 ? maper(str) : 0;
	ft_strdel(&line);
	m->map = (char**)malloc(sizeof(char*) * m->n.n_l);
	while (get_next_line(fd, &line) > 0)
	{
		if ((int)ft_strlen(line) != m->n.s_l || i == m->n.n_l)
			maper(str);
		m->map[i] = line;
		i++;
	}
	i != m->n.n_l ? maper(str) : 0;
	ft_strdel(&line);
	validmap(m, str);
	close(fd);
}
