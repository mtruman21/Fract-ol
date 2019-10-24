/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtruman <mtruman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:10:11 by mtruman           #+#    #+#             */
/*   Updated: 2019/09/10 17:13:55 by mtruman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <math.h>

static t_img	mandelbrot_init(int x, int y, t_env *e, t_img *c)
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
	c->real = min_x + (max_x - min_x) / W_WIDTH * (x);
	c->img = min_y + (max_y - min_y) / W_HEIGHT * (y);
	z.real = 0;
	z.img = 0;
	return (z);
}

static void		mandelbrot_col(t_env *e, int y, t_img *c)
{
	int			x;
	int			i;
	int			color;
	t_img		z;
	t_img		tmp;

	x = 0;
	while (x < W_WIDTH)
	{
		z = mandelbrot_init(x, y, e, c);
		i = 0;
		while (i < (int)(e->it + (e->fractal.zoom / 1000) * e->fractal.gen))
		{
			tmp.img = z.img;
			tmp.real = z.real;
			z.real = tmp.real * tmp.real - tmp.img * tmp.img + c->real;
			z.img = 2 * tmp.real * tmp.img + c->img;
			if (z.real * z.real + z.img * z.img >= 4)
				break ;
			i++;
		}
		color = choose_color1(i, e);
		verif_print(e, x, y, color);
		x++;
	}
}

void			draw_mandelbrot(t_env *e)
{
	t_img	img;

	while (e->start < e->finish)
	{
		mandelbrot_col(e, e->start++, &img);
	}
}
