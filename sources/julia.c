/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtruman <mtruman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:10:11 by mtruman           #+#    #+#             */
/*   Updated: 2019/09/10 17:13:57 by mtruman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <math.h>

static t_img	julia_init(int x, int y, t_env *e, t_img *c)
{
	t_img		z;
	double		min_x;
	double		max_x;
	double		min_y;
	double		max_y;

	min_x = (-e->fractal.max_x / e->fractal.zoom) + e->fractal.pos_x;
	max_x = (e->fractal.max_x / e->fractal.zoom) + e->fractal.pos_x;
	min_y = (-e->fractal.max_y / e->fractal.zoom) + e->fractal.pos_y;
	max_y = (e->fractal.max_y / e->fractal.zoom) + e->fractal.pos_y;
	z.real = min_x + (max_x - min_x) / W_WIDTH * (x);
	z.img = min_y + (max_y - min_y) / W_HEIGHT * (y);
	c->real = 4 * ((e->clic.x * 0.5) / (long double)W_WIDTH);
	c->img = 4 * ((e->clic.y * 0.5) / (long double)W_HEIGHT);
	return (z);
}

static void		julia_col(t_env *e, int y, t_img *c)
{
	int			x;
	int			i;
	int			color;
	t_img		z;
	t_img		tmp;

	x = 0;
	while (x < W_WIDTH)
	{
		z = julia_init(x, y, e, c);
		i = 0;
		while (i < e->it)
		{
			tmp.img = z.img;
			tmp.real = z.real;
			z.real = tmp.real * tmp.real - tmp.img * tmp.img + e->clic.x;
			z.img = 2 * tmp.real * tmp.img + e->clic.y;
			if (z.real * z.real + z.img * z.img >= 4)
				break ;
			i++;
		}
		color = choose_color1(i, e);
		verif_print(e, x, y, color);
		x++;
	}
}

void			draw_julia(t_env *e)
{
	t_img	img;

	while (e->start < e->finish)
	{
		julia_col(e, e->start++, &img);
	}
}
