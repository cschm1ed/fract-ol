/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_key_events.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:46:19 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/14 23:49:37 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	modify_color(int keysym, t_ui *ui);
static void	move_view(int keysym, t_ui *ui);
static void	shifts(int keysym, t_ui *ui);

/**
 * handle_keypress - Handles keypress events for the fractal viewer.
 * @keysym: The pressed key symbol
 * @ui: pointer to the user interface structure
 *
 * Calls the appropriate functions based on the pressed key symbol.
 * Returns 0.
 */

int	handle_keypress(int keysym, t_ui *ui)
{
	if (keysym == XK_Escape)
		fractol_quit(ui);
	else if (keysym == XK_1 || keysym == XK_2 || keysym == XK_3
		|| keysym == XK_4 || keysym == XK_r || keysym == XK_g
		|| keysym == XK_b || keysym == XK_n || keysym == XK_h
		|| keysym == XK_t)
		modify_color(keysym, ui);
	else if (keysym == XK_a || keysym == XK_s || keysym == XK_y
		|| keysym == XK_x || keysym == XK_l || keysym == XK_p
		|| keysym == XK_space)
		shifts(keysym, ui);
	else if (keysym == XK_Up || keysym == XK_Down || keysym == XK_Left
		|| keysym == XK_Right)
		move_view(keysym, ui);
	else if (keysym == XK_plus)
	{
		ui->this.i_max += 10;
		ui->redraw = 1;
	}
	else if (keysym == XK_minus)
	{
		ui->this.i_max -= 10;
		ui->redraw = 1;
	}
	return (0);
}

/**
 * move_view - Moves the fractal view based on the pressed arrow key.
 * @keysym: The pressed arrow key symbol
 * @ui: pointer to the user interface structure
 *
 * Updates the bounds and sets the redraw flag based on the pressed arrow key.
 */

static void	move_view(int keysym, t_ui *ui)
{
	t_this	*this;

	this = &ui->this;
	if (keysym == XK_Down)
	{
		this->lower_bounds.y += ZOOM_RATE * this->rd.y;
		this->upper_bounds.y += ZOOM_RATE * this->rd.y;
	}
	else if (keysym == XK_Right)
	{
		this->lower_bounds.x += ZOOM_RATE * this->rd.x;
		this->upper_bounds.x += ZOOM_RATE * this->rd.x;
	}
	else if (keysym == XK_Up)
	{
		this->lower_bounds.y -= ZOOM_RATE * this->rd.y;
		this->upper_bounds.y -= ZOOM_RATE * this->rd.y;
	}
	else if (keysym == XK_Left)
	{
		this->lower_bounds.x -= ZOOM_RATE * this->rd.x;
		this->upper_bounds.x -= ZOOM_RATE * this->rd.x;
	}
	ui->redraw = 1;
}

/**
 * modify_color - Modifies the color scheme based on the pressed key.
 * @keysym: The pressed key symbol
 * @ui: pointer to the user interface structure
 *
 * Updates the color scheme and sets the redraw flag based on the pressed key.
 */

static void	modify_color(int keysym, t_ui *ui)
{
	t_this	*this;

	this = &ui->this;
	if (keysym == XK_1)
	{
		this->rs = 0;
		this->gs = 0;
		this->bs = 0;
	}
	else if (keysym == XK_2)
		this->calculate_color = &continous_coloring;
	else if (keysym == XK_3)
		this->calculate_color = &interpolation;
	else if (keysym == XK_4)
		this->calculate_color = &psych1;
	this->rs += MANUAL_SHIFT * (keysym == XK_r);
	this->gs += MANUAL_SHIFT * (keysym == XK_g);
	this->bs += MANUAL_SHIFT * (keysym == XK_b);
	this->rs -= MANUAL_SHIFT * (keysym == XK_t);
	this->gs -= MANUAL_SHIFT * (keysym == XK_h);
	this->bs -= MANUAL_SHIFT * (keysym == XK_n);
	ui->redraw = 1;
}

/**
 * shifts - Updates the shift state or party mode used to change the colors
 * based on the pressed key.
 * @keysym: The pressed key symbol
 * @ui: pointer to the user interface structure
 *
 * Sets the shift state or party mode flag based on the pressed key.
 */

static void	shifts(int keysym, t_ui *ui)
{
	if (keysym == XK_p)
		ui->party = 1;
	else if (keysym == XK_l)
		ui->party = 0;
	else if (keysym == XK_a)
		ui->shift = 1;
	else if (keysym == XK_y)
		ui->shift = 2;
	else if (keysym == XK_s)
		ui->shift = -1;
	else if (keysym == XK_x)
		ui->shift = -2;
	else if (keysym == XK_space)
		ui->shift = 0;
}
