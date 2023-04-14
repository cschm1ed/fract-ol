/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_calculations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:16:17 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/14 23:41:04 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int	check_q(long double q, t_ui *ui);

/**
 * iterations_mandelbrot - calculates the number of Mandelbrot set iterations
 * @ui: pointer to the user interface structure containing the Mandelbrot data
 *
 * This function calculates the number of Mandelbrot set iterations for the
 * given coordinates. It implements an optimized escape-time algorithm.
 *
 * Return: the number of iterations required to escape
 */

int	iterations_mandelbrot(t_ui *ui)
{
	t_complex	temp;
	t_complex	coords;
	t_this		*this;
	long double	q;
	int			i;

	i = 0;
	this = &ui->this;
	coords = this->rc;
	temp.x = pow(this->rc.x, 2);
	temp.y = pow(this->rc.y, 2);
	q = pow(coords.x - 0.25, 2) + pow(coords.y, 2);
	if (check_q(q, ui))
		return (this->i_max);
	while (i < this->i_max && temp.x + temp.y < 4)
	{
		coords.y = 2 * coords.x * coords.y + this->rc.y;
		coords.x = temp.x - temp.y + this->rc.x;
		temp.x = pow(coords.x, 2);
		temp.y = pow(coords.y, 2);
		i ++;
	}
	return (i);
}

/**
 * iterations_julia - calculates the number of Julia set iterations
 * @ui: pointer to the user interface structure containing the Julia data
 *
 * This function calculates the number of Julia set iterations for the
 * given coordinates. It implements an escape-time algorithm.
 *
 * Return: the number of iterations required to escape
 */

int	iterations_julia(t_ui *ui)
{
	t_complex	temp;
	t_complex	coords;
	t_this		*this;
	int			i;

	i = 0;
	this = &ui->this;
	temp.x = pow(this->rc.x, 2);
	temp.y = pow(this->rc.y, 2);
	coords = this->rc;
	while (i < this->i_max && temp.x + temp.y < 4)
	{
		coords.y = 2 * coords.x * coords.y + this->julia_constants.y;
		coords.x = temp.x - temp.y + this->julia_constants.x;
		temp.x = pow(coords.x, 2);
		temp.y = pow(coords.y, 2);
		i ++;
	}
	return (i);
}

/**
 * iterations_burning_ship - calculates the number of Burning Ship iterations
 * @ui: pointer to the user interface structure containing the Burning Ship data
 *
 * This function calculates the number of Burning Ship fractal iterations for
 * the given coordinates. It implements an escape-time algorithm.
 *
 * Return: the number of iterations required to escape
 */

int	iterations_burning_ship(t_ui *ui)
{
	t_complex	temp;
	t_complex	coords;
	t_this		*this;
	int			i;

	i = 0;
	this = &ui->this;
	temp.x = 0;
	temp.y = 0;
	coords = this->rc;
	while (i < this->i_max && temp.x + temp.y < 4)
	{
		coords.y = fabsl(2 * coords.x * coords.y) + this->rc.y;
		coords.x = temp.x - temp.y + this->rc.x;
		temp.x = pow(coords.x, 2);
		temp.y = pow(coords.y, 2);
		i ++;
	}
	return (i);
}

/**
 * check_q - checks if a given point is in the main cardioid or period-2 bulb
 * @q: long double value used in the Mandelbrot set iteration optimization
 * @ui: pointer to the user interface structure containing the Mandelbrot data
 *
 * This helper function is used to optimize the Mandelbrot set algorithm. It
 * checks if a given point is in the main cardioid or period-2 bulb of the
 * Mandelbrot set.
 *
 * Return: the maximum number of iterations if in cardioid or period-2 bulb, 0 otherwise
 */

static int	check_q(long double q, t_ui *ui)
{
	t_this		*this;
	t_complex	coords;

	this = &ui->this;
	coords = this->rc;
	q = pow(coords.x - 0.25, 2) + pow(coords.y, 2);
	if (q * (q + (coords.x - 0.25)) < 0.25 * pow(coords.y, 2))
		return (this->i_max);
	else if (pow(coords.x, 2) + (2 * coords.x) + 1
		+ pow(coords.y, 2) < 0.0625)
		return (this->i_max);
	return (0);
}
