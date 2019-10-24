/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtruman <mtruman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:10:11 by mtruman           #+#    #+#             */
/*   Updated: 2019/09/10 17:36:02 by mtruman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void		clear_img(t_env *win)
{
	ft_bzero(win->img.data, W_WIDTH * W_HEIGHT * 4);
	mlx_put_image_to_window(win->mlx, win->win, win->img.ptr, 0, 0);
}

int			init(t_env *e)
{
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, W_WIDTH, W_HEIGHT, "fractol");
	e->fractal.gen = 2;
	e->fractal.zoom = 1.0;
	e->fractal.pos_x = 0.0;
	e->fractal.pos_y = 0.0;
	e->fractal.max_x = 2.4;
	e->fractal.max_y = 1.5;
	e->clic.active = 0;
	e->clic.x = 50;
	e->clic.y = 20;
	e->it = 50;
	e->color = 1;
	e->img.ptr = mlx_new_image(e->mlx, W_WIDTH, W_HEIGHT);
	e->img.data = mlx_get_data_addr(e->img.ptr, &e->img.bpp, &e->img.size_line,\
	&e->img.endian);
	return (0);
}

void		ft_usage(void)
{
	ft_putendl("usage : ./fractol [ID]");
	ft_putendl("(1) Mandelbrot");
	ft_putendl("(2) Julia");
	ft_putendl("(3) Brain");
	ft_putendl("(4) Burning Ship");
	ft_putendl("After PRESS ANY buttom");
	exit(-1);
}

int			main(int argc, char **argv)
{
	t_env		e;
	int			arg;

	if (argc > 1 && argc < 3 && ft_strlen(argv[1]) == 1)
	{
		arg = ft_atoi(argv[1]);
		if (arg != 1 && arg != 2 && arg != 3 && arg != 4)
		{
			ft_usage();
			return (0);
		}
		e.numb = ft_atoi(argv[1]);
		init(&e);
		controls(&e);
		mlx_loop(e.mlx);
	}
	else
		ft_usage();
	return (0);
}
