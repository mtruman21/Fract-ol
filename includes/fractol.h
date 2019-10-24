/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtruman <mtruman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:10:11 by mtruman           #+#    #+#             */
/*   Updated: 2019/09/10 17:14:09 by mtruman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define ZOOM 10
# define ORIGINE_X 500
# define ORIGINE_Y 700
# define W_WIDTH 1000
# define W_HEIGHT 1000
# define MAX_IT 60
# define NUM_THREADS 10
# include <mlx.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <libft.h>
# include <pthread.h>

typedef struct		s_image
{
	void			*ptr;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
}					t_image;

typedef struct		s_fractal
{
	int				id;
	float			zoom;
	float			pos_x;
	float			pos_y;
	double			max_x;
	double			max_y;
	int				gen;
}					t_fractal;

typedef struct		s_clic
{
	int				active;
	double			x;
	double			y;
}					t_clic;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	int				it;
	t_fractal		fractal;
	t_clic			clic;
	t_image			img;
	int				start;
	int				finish;
	int				numb;
	int				butt;
	int				color;
}					t_env;

typedef struct		s_img
{
	double		img;
	double		real;
}					t_img;

int					rgb_to_i(int r, int g, int b);
void				verif_print(t_env *e, int x, int y, int color);
void				controls(t_env *param);
void				render(t_env *win, void (f)(t_env *win));
void				clear_img(t_env *win);
void				draw_burning_ship(t_env *e);
int					mouse_press(int key, int x, int y, t_env *param);
int					mouse_release(int key, int x, int y, t_env *param);
int					key_press(int keycode, t_env *param);
void				reset(t_env *e);
int					press_hook(int keycode, int x, int y, t_env *e);
int					release_hook(int keycode, int x, int y, t_env *e);
int					hook(int x, int y, t_env *e);
void				draw_julia(t_env *e);
void				draw_mandelbrot(t_env *e);
void				draw_brain(t_env *e);
int					choose_color1(int i, t_env *e);

#endif
