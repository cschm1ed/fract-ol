/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils_custom.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:13:15 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/14 23:35:42 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

/**
 * put_pixel - places a pixel on the UI image
 * @x: the x-coordinate of the pixel
 * @y: the y-coordinate of the pixel
 * @color: the color of the pixel
 * @ui: pointer to the UI structure
 * 
 * Puts a pixel with the specified color at the given coordinates in the UI image.
 */

void	put_pixel(int x, int y, int color, t_ui *ui)
{
	char	*dst;

	dst = ui->img_addr + (y * ui->line_length + x * ui->bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}

/**
 * trgb - converts individual color components into a single integer
 * @t: transparency component
 * @r: red component
 * @g: green component
 * @b: blue component
 * 
 * Combines transparency, red, green, and blue components into a single integer.
 * 
 * Return: the combined color value as an integer
 */

int	trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/**
 * fractol_quit - cleans up and exits the fractal program
 * @ui: pointer to the UI structure
 * 
 * Destroys the UI resources, frees memory, and exits the program.
 * 
 * Return: 0 (should never be reached)
 */

int	fractol_quit(t_ui *ui)
{
	mlx_destroy_image(ui->mlx, ui->img);
	mlx_destroy_window(ui->mlx, ui->win);
	free(ui->mlx);
	exit(0);
	return (0);
}

/**
 * print_help - prints help information for the fractal program
 * 
 * Displays help information on how to interact with the fractal program,
 * including controls and available inputs.
 */

void	print_help(void)
{
	ft_putstr("Here are ways to interact with the fractol:\n");
	ft_putstr("You can zoom in and out of the picture using the mouse\n");
	ft_putstr("and move around with the arrow keys.\n");
	ft_putstr("Number keys 2-4 will change the coloring mode.\n");
	ft_putstr("Press 'p' to start tbe party mode ");
	ft_putstr("and 'l' to stop it.\n");
	ft_putstr("'r', 'g', 'b' will increase their ");
	ft_putstr("respective color values,\n");
	ft_putstr("and 't', 'h', 'n' decrease them. '1' will reset them.\n");
	ft_putstr("'a', 's' 'y' and 'x' will automaticall change ");
	ft_putstr("julia-set constants.\n");
}

/**
 * print_error - prints error information for the fractal program
 * 
 * Displays an error message with information on the correct input format
 * and available options for the fractal program.
 */

void	print_error(void)
{
	ft_putstr("Wrong inputs! Available inputs are:\n");
	ft_putstr("\"./fractol 'mandelbrot' [width]\"\n");
	ft_putstr("\"./fractol 'burning ship' [width]\"\n");
	ft_putstr("\"./fractol 'julia' [width] [x] [y]\"\n");
	ft_putstr("Where'x' and 'y' are constants used to render");
	ft_putstr(" the julia set.");
	ft_putstr("Their value must be between -2 and 2.\n");
	ft_putstr("Use \"./fractol help\" for more information.\n");
}
