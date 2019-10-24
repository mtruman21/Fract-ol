/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtruman <mtruman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:41:52 by mtruman           #+#    #+#             */
/*   Updated: 2019/09/10 17:14:10 by mtruman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	zoom(int keycode, double x, double y, t_env *e)
{
	float	direction;

	direction = keycode == 4 ? 0.9 : 1.05;
	e->fractal.zoom *= (direction);
	e->fractal.pos_x += (x / (W_WIDTH / 2)) / e->fractal.zoom;
	e->fractal.pos_y += (y / (W_HEIGHT / 2)) / e->fractal.zoom;
}

int		mouse_press(int key, int x, int y, t_env *param)
{
	float direction;

	direction = key == 4 ? 0.9 : 1.05;
	if (key == 1)
		param->butt = 1;
	if (key == 5 || key == 4)
		zoom(key, x - (W_WIDTH / 2), y - (W_HEIGHT / 2), param);
	key_press(400, param);
	return (0);
}

int		mouse_release(int key, int x, int y, t_env *param)
{
	(void)x;
	(void)y;
	if (key == 1)
		param->butt = 0;
	return (0);
}

void	render(t_env *win, void (f)(t_env *win))
{
	pthread_t	threads[NUM_THREADS];
	t_env		fact[NUM_THREADS];
	int			i;

	i = 0;
	ft_bzero(win->img.data, W_WIDTH * W_HEIGHT * 4);
	while (i < NUM_THREADS)
	{
		fact[i] = *win;
		fact[i].start = i * (W_HEIGHT / NUM_THREADS);
		fact[i].finish = (i + 1) * (W_HEIGHT / NUM_THREADS);
		if (pthread_create(&threads[i], NULL, \
		(void *(*)(void *))f, (void *)&fact[i]))
		{
			ft_putendl("thread error");
			return ;
		}
		i++;
	}
	while (i-- > 0)
		if (pthread_join(threads[i], NULL))
			ft_putendl("join error");
	mlx_put_image_to_window(win->mlx, win->win, win->img.ptr, 0, 0);
}
