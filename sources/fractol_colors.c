/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 11:15:12 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/14 23:43:38 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/**
 * continous_coloring - calculates the continuous coloring for a given value
 * @t: long double value representing the point in the continuous color spectrum
 * @this: pointer to the structure containing color data
 *
 * This function calculates the continuous coloring based on the input value t.
 * It generates the red, green, and blue components using a smooth color gradient.
 *
 * Return: the continuous color as an integer value (in the format 0x00RRGGBB)
 */

int	continous_coloring(long double t, t_this *this)
{
	int	r;
	int	g;
	int	b;

	if (t == 1)
		return (trgb(0, 0, 0, 0));
	r = 9 * (1 - t + this->rs) * pow(t + this->rs, 3) * 255;
	g = 15 * pow((1 - (t + this->gs)), 2) * pow(t + this->gs, 2) * 255;
	b = 8.5 * pow((1 - (t + this->bs)), 3) * t * 255;
	return (trgb(0, r, g, b));
}

/**
 * interpolation - calculates the color using interpolation for a given value
 * @t: long double value representing the point in the color interpolation
 * @this: pointer to the structure containing color data
 *
 * This function calculates the color based on the input value t using
 * interpolation. It generates the red, green, and blue components by
 * applying trigonometric functions on t.
 *
 * Return: the interpolated color as an integer value (in the format 0x00RRGGBB)
 */

int	interpolation(long double t, t_this *this)
{
	int	r;
	int	g;
	int	b;

	t *= 3.14 / 2;
	if (t >= 0.99)
		return (0);
	r = fabs(sin(t + this->rs) * 255);
	g = fabs(tan(t + this->gs) * 255 * 0.5);
	b = fabs(sin(t + this->bs + 0.25) * 255);
	return (trgb(0, r, g, b));
}

/**
 * psych1 - calculates color for a given value
 * @t: long double value representing the point in the psychedelic color spectrum
 * @this: pointer to the structure containing color data
 *
 * This function calculates the coloring based on the input value t.
 * It generates the red, green, and blue components using a smooth color gradient
 * and a logarithmic transformation of t. Due to potential overflows, it leads
 * to unpredictable colors, giving a more random and psychedelic appearance.
 *
 * Return: the unpredictable psychedelic color as an integer value (in the format 0x00RRGGBB)
 */

int	psych1(long double t, t_this *this)
{
	int	r;
	int	g;
	int	b;

	if (t == 1)
		return (trgb(0, 0, 0, 0));
	t = -log(t) * 0.5;
	r = 9 * (1 - t + this->rs) * pow(t + this->rs, 3) * 255;
	g = 15 * pow((1 - (t + this->gs)), 2) * pow(t + this->gs, 2) * 255;
	b = 8.5 * pow((1 - (t + this->bs)), 3) * t * 255;
	return (trgb(0, r, g, b));
}
