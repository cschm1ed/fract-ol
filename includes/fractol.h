/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 09:07:50 by cschmied          #+#    #+#             */
/*   Updated: 2023/03/03 09:40:20 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../mlx/mlx.h"
# include <keysym.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/errno.h>
# include <stdio.h>

# define UPPER_BOUND 2
# define LOWER_BOUND -2
# define JULIA_CONSTANT_UPPER 2
# define JULIA_CONSTANT_LOWER -2
# define SHIFT_RATE 0.01
# define PARTY_RATE -0.01
# define MANUAL_SHIFT 0.05
# define ZOOM_RATE 0.05

typedef struct s_this		t_this;
typedef struct s_ui			t_ui;
typedef struct s_complex	t_complex;

typedef struct s_complex
{
	long double	x;
	long double	y;
}				t_complex;

typedef struct s_this
{
	t_complex	lower_bounds;
	t_complex	upper_bounds;
	t_complex	pd;
	t_complex	rd;
	t_complex	rc;
	t_complex	pc;
	t_complex	julia_constants;
	int			i_max;
	int			(*calculate_color)(long double t, t_this *this);
	int			(*calculate_iterations)(t_ui *ui);
	double		rs;
	double		gs;
	double		bs;
}				t_this;

typedef struct s_ui
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_addr;
	char		*titel;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	int			redraw;
	int			shift;
	int			party;
	double		scroll_rate;
	t_this		this;
}				t_ui;

//fractol_draw
void		draw_fractal(t_ui *ui);

//fractol_utils.c
long double	ft_atod(const char *str);
int			ft_strisnum(char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_atoi(const char *str);
int			trgb(int t, int r, int g, int b);
int			fractol_quit(t_ui *ui);
int			ft_strlen(const char *str);
char		*ft_strlower(char *str);
void		ft_putstr(const char *str);
void		put_pixel(int x, int y, int color, t_ui *ui);
void		print_error(void);
void		print_help(void);

//fractol_init.c
int			init_inputs(t_ui *ui, char **argv, int argc);
int			ui_init(t_ui *ui, char **argv);
void		this_init(t_ui *ui);
void		wrong_input(int help);
void		julia_init(t_ui *ui, char **argv);

//fractol events
int			handle_mouse(int button, int x, int y, t_ui *ui);
int			handle_keypress(int keysym, t_ui *ui);
int			handle_no_event(t_ui *ui);

//fractol colors
int			continous_coloring(long double t, t_this *this);
int			interpolation(long double t, t_this *this);
int			psych1(long double t, t_this *this);

//fractol calculations
int			iterations_mandelbrot(t_ui *ui);
int			iterations_julia(t_ui *ui);
int			iterations_burning_ship(t_ui *ui);

#endif