/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtruman <mtruman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 15:30:05 by mtruman           #+#    #+#             */
/*   Updated: 2019/09/10 17:13:58 by mtruman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <math.h>

int			colcol(int color, int i, t_env *e)
{
	int tmp;

	if (e->fractal.gen)
		tmp = (int)(MAX_IT + e->fractal.zoom / 1000);
	else
		tmp = MAX_IT;
	if (i == tmp)
		color = rgb_to_i(200, 190, 120);
	else
		color = rgb_to_i(sin((float)i / ((float)MAX_IT / 2)) * 255, 0, 0);
	return (color);
}

int			choose_color1(int i, t_env *e)
{
	int			color;

	if (e->color == 1)
	{
		if (i == MAX_IT)
			color = rgb_to_i(240, 230, 10);
		else
			color = rgb_to_i(sin((float)i / ((float)MAX_IT / 4)) * 255, \
				sin((float)i / ((float)MAX_IT)) * 255, 0);
	}
	if (e->color == 2)
		color = colcol(color, i, e);
	if (e->color == 3)
	{
		if (i == MAX_IT)
			color = rgb_to_i(240, 230, 10);
		else
			color = rgb_to_i(sin((float)i / ((float)MAX_IT / 2)) * 255,\
			sin((float)i / ((float)MAX_IT / 3.5)) * 255, 0);
	}
	return (color);
}

void		reset(t_env *e)
{
	e->fractal.gen = 2;
	e->fractal.zoom = 1.0;
	e->fractal.pos_x = 0.0;
	e->fractal.pos_y = 0.0;
	e->fractal.max_x = 2.4;
	e->fractal.max_y = 1.5;
	e->clic.active = 0;
	e->clic.x = 0.6;
	e->clic.y = -0.8;
	e->it = 50;
}

int			rgb_to_i(int r, int g, int b)
{
	int		rgb;

	rgb = r;
	rgb = (rgb << 8) + g;
	rgb = (rgb << 8) + b;
	return (rgb);
}

void		verif_print(t_env *e, int x, int y, int color)
{
	int		index;

	index = 0;
	if (x >= 0 && x <= W_WIDTH && y >= 0 && y <= W_HEIGHT)
	{
		index = y * e->img.size_line + x * (e->img.bpp / 8);
		e->img.data[index] = color;
		e->img.data[index + 1] = color >> 8;
		e->img.data[index + 2] = color >> 16;
	}
}
