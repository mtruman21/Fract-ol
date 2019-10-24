/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtruman <mtruman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:10:11 by mtruman           #+#    #+#             */
/*   Updated: 2019/09/10 17:13:56 by mtruman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include "../libft/libft.h"
#include "mlx.h"

int		julia_motion(int x, int y, t_env *fractol)
{
	if (fractol->butt == 1)
	{
		fractol->clic.x = 4 * ((double)x / W_WIDTH - 0.5);
		fractol->clic.y = 4 * ((double)(W_HEIGHT - y) / W_HEIGHT - 0.5);
	}
	if (fractol->numb == 2)
		render(fractol, draw_julia);
	return (0);
}

void	draw_fract(t_env *param)
{
	if (param->numb == 1)
		render(param, draw_mandelbrot);
	if (param->numb == 2)
		render(param, draw_julia);
	if (param->numb == 3)
		render(param, draw_brain);
	if (param->numb == 4)
		render(param, draw_burning_ship);
	mlx_put_image_to_window(param->mlx, param->win, param->img.ptr, 0, 0);
}

void	offset(int keycode, t_env *param)
{
	if (keycode == 125)
		param->fractal.pos_y -= 0.010;
	if (keycode == 12226)
		param->fractal.pos_y += 0.010;
	if (keycode == 123)
		param->fractal.pos_x += 0.010;
	if (keycode == 124)
		param->fractal.pos_x -= 0.010;
	if (keycode == 69)
		param->it += 1;
	if (keycode == 78)
		param->it -= 1;
	if (keycode == 76)
		param->fractal.zoom *= 1.2;
	if (keycode == 65)
		param->fractal.zoom *= 0.8;
	if (keycode == 53)
	{
		exit(0);
		mlx_destroy_window(param->mlx, param->win);
	}
}

int		key_press(int keycode, t_env *param)
{
	if (keycode == 1)
	{
		if (param->color != 1)
			param->color -= 1;
	}
	if (keycode == 2)
	{
		if (param->color != 3)
			param->color += 1;
	}
	if (keycode == 18)
		param->numb = 1;
	if (keycode == 19)
		param->numb = 2;
	if (keycode == 15)
		reset(param);
	if (keycode == 20)
		param->numb = 3;
	if (keycode == 21)
		param->numb = 4;
	if (keycode > 49)
		offset(keycode, param);
	clear_img(param);
	draw_fract(param);
	return (0);
}

void	controls(t_env *param)
{
	mlx_hook(param->win, 2, 0, key_press, param);
	mlx_hook(param->win, 6, 0, julia_motion, param);
	mlx_hook(param->win, 4, 0, mouse_press, param);
	mlx_hook(param->win, 5, 0, mouse_release, param);
	mlx_hook(param->win, 17, 0, close, param);
}
