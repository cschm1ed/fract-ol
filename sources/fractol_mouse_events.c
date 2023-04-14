/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_mouse_events.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:00:48 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/14 23:51:13 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	zoom_out(t_ui *ui, int x, int y);
static void	zoom_in(t_ui *ui, int x, int y);

/**
 * handle_mouse - Handles mouse events for the fractal viewer
 * @button: mouse button that was pressed or released
 * @x: x-coordinate of the mouse cursor
 * @y: y-coordinate of the mouse cursor
 * @ui: pointer to the user interface structure
 *
 * Processes mouse events such as zooming in and out, and switching between
 * Mandelbrot and Julia fractals.
 * Returns 0 on success.
 */

int	handle_mouse(int button, int x, int y, t_ui *ui)
{
	if (button == 5)
		zoom_in(ui, x, y);
	else if (button == 4)
		zoom_out(ui, x, y);
	else if (button == 1)
	{
		if (ui->this.calculate_iterations == &iterations_mandelbrot)
		{
			ui->this.calculate_iterations = &iterations_julia;
			ui->this.julia_constants.x = x * ui->this.pd.x
				+ ui->this.lower_bounds.x;
			ui->this.julia_constants.y = ui->this.upper_bounds.y
				- y * ui->this.pd.y;
			ui->redraw = 1;
		}
	}
	else if (button == 3)
	{
		if (ui->this.calculate_iterations == &iterations_julia)
		{
			ui->this.calculate_iterations = &iterations_mandelbrot;
			ui->redraw = 1;
		}
	}
	return (0);
}

/**
 * zoom_in - Zooms in on the fractal at the specified coordinates
 * @ui: pointer to the user interface structure
 * @x: x-coordinate of the zoom center
 * @y: y-coordinate of the zoom center
 *
 * Adjusts the bounds of the fractal view to zoom in at the given coordinates.
 * Updates the redraw flag.
 */

static void	zoom_in(t_ui *ui, int x, int y)
{
	t_this	*this;

	this = &ui->this;
	this->lower_bounds.x += ZOOM_RATE * this->pd.x * x;
	this->upper_bounds.x -= ZOOM_RATE * (this->pd.x * (ui->width - x));
	this->upper_bounds.y -= ZOOM_RATE * this->pd.y * (ui->height - y);
	this->lower_bounds.y += ZOOM_RATE * (this->pd.y * y);
	ui->redraw = 1;
}

/**
 * zoom_out - Zooms out of the fractal at the specified coordinates
 * @ui: pointer to the user interface structure
 * @x: x-coordinate of the zoom center
 * @y: y-coordinate of the zoom center
 *
 * Adjusts the bounds of the fractal view to zoom out at the given coordinates.
 * Updates the redraw flag.
 */

static void	zoom_out(t_ui *ui, int x, int y)
{
	t_this	*this;

	this = &ui->this;
	this->lower_bounds.x -= ZOOM_RATE * this->pd.x * (ui->width - x);
	this->upper_bounds.x += ZOOM_RATE * this->pd.x * x;
	this->upper_bounds.y += ZOOM_RATE * this->pd.y * y;
	this->lower_bounds.y -= ZOOM_RATE * this->pd.y * (ui->height - y);
	ui->redraw = 1;
}
