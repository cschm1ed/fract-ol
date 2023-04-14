/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:49:05 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/14 23:44:44 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/**
 * draw_fractal - draws a fractal on the user interface
 * @ui: pointer to the user interface structure containing fractal data
 *
 * This function iterates through the user interface's width and height,
 * calculates the real and imaginary coordinates (rc) for each pixel, and
 * computes the number of iterations using the calculate_iterations function.
 * It then calculates the color for each pixel using the calculate_color
 * function and puts the pixel on the user interface.
 */

void	draw_fractal(t_ui *ui)
{
	t_this		*this;
	long double	iterations;

	this = &ui->this;
	this->pc.y = 0;
	while (this->pc.y < ui->height)
	{
		this->pc.x = 0;
		this->rc.y = this->lower_bounds.y
			+ this->pc.y * this->pd.y;
		while (this->pc.x < ui->width)
		{
			this->rc.x = this->lower_bounds.x
				+ this->pc.x * this->pd.x;
			iterations = (long double)this->calculate_iterations(ui)
				/ this->i_max;
			put_pixel(this->pc.x, this->pc.y,
				this->calculate_color(iterations, this), ui);
			this->pc.x++;
		}
		this->pc.y++;
	}
}
