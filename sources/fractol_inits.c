/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_inits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 09:27:50 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/14 23:46:40 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/**
 * ui_init - initializes the user interface structure
 * @ui: pointer to the user interface structure to be initialized
 * @argv: array of command line arguments
 *
 * Initializes the user interface structure by setting up the mlx instance,
 * window, image, and other related attributes. Returns 1 if successful,
 * otherwise returns 0.
 */

int	ui_init(t_ui *ui, char **argv)
{
	ui->mlx = mlx_init();
	if (!ui->mlx)
		return (1);
	ui->width = ft_atoi(argv[2]);
	ui->height = (ui->width / 16) * 9;
	ui->scroll_rate = 0.05;
	ui->titel = argv[1];
	ui->win = mlx_new_window(ui->mlx, ui->width, ui->height, ui->titel);
	if (!ui->win)
		return (free(ui->mlx), 0);
	ui->img = mlx_new_image(ui->mlx, ui->width, ui->height);
	ui->img_addr = mlx_get_data_addr(ui->img,
			&ui->bits_per_pixel, &ui->line_length, &ui->endian);
	ui->redraw = 0;
	ui->shift = 0;
	return (1);
}

/**
 * this_init - initializes the fractal structure
 * @ui: pointer to the user interface structure containing the fractal data
 *
 * Initializes the fractal structure by setting up the initial values for
 * the iteration count, bounds, and color functions.
 */

void	this_init(t_ui *ui)
{
	t_this	*this;

	this = &ui->this;
	this->i_max = 80;
	this->lower_bounds.x = LOWER_BOUND;
	this->upper_bounds.x = UPPER_BOUND;
	this->lower_bounds.y = (this->lower_bounds.x / 16) * 9;
	this->upper_bounds.y = (this->upper_bounds.x / 16) * 9;
	this->rd.y = this->upper_bounds.y - this->lower_bounds.y;
	this->rd.x = this->upper_bounds.x - this->lower_bounds.x;
	this->pd.x = this->rd.x / ui->width;
	this->pd.y = this->rd.y / ui->height;
	this->rs = 0;
	this->gs = 0;
	this->bs = 0;
	this->calculate_color = continous_coloring;
}

/**
 * init_inputs - processes command line arguments and initializes
 *               the appropriate fractal functions
 * @ui: pointer to the user interface structure
 * @argv: array of command line arguments
 * @argc: number of command line arguments
 *
 * Processes the command line arguments and initializes the appropriate
 * fractal functions for Mandelbrot, Julia, or Burning Ship fractals.
 * Returns 1 if successful, otherwise calls wrong_input and exits.
 */

int	init_inputs(t_ui *ui, char **argv, int argc)
{
	t_this	*this;

	this = &ui->this;
	if (ft_strcmp(ft_strlower(argv[1]), "help") == 0)
		wrong_input(1);
	if (ft_strcmp(ft_strlower(argv[1]), "mandelbrot") == 0)
	{
		if (argc == 3 && ft_strisnum(argv[2]))
			this->calculate_iterations = iterations_mandelbrot;
		else
			wrong_input(0);
	}
	else if (ft_strcmp(ft_strlower(argv[1]), "julia") == 0)
	{
		if (argc == 5 && ft_strisnum(argv[2]) && ft_strisnum(argv[3])
			&& ft_strisnum(argv[4]))
			julia_init(ui, argv);
		else
			wrong_input(0);
	}
	else if (ft_strcmp(ft_strlower(argv[1]), "burning ship") == 0)
		this->calculate_iterations = iterations_burning_ship;
	else
		wrong_input(0);
	return (1);
}

/**
 * julia_init - initializes the Julia fractal constants
 * @ui: pointer to the user interface structure containing the fractal data
 * @argv: array of command line arguments
 *
 * Initializes the Julia fractal constants (real and imaginary parts)
 * based on the command line arguments.
 */

void	julia_init(t_ui *ui, char **argv)
{
	t_this	*this;

	this = &ui->this;
	this->julia_constants.x = ft_atod(argv[3]);
	this->julia_constants.y = ft_atod(argv[4]);
	this->calculate_iterations = iterations_julia;
}

/**
 * wrong_input - handles wrong command line inputs and displays help or error
 * @help: integer flag indicating whether to display help (1) or error (0)
 *
 * Handles wrong command line inputs by displaying help or error messages.
 * Exits the program with an exit code of 1.
 */

void	wrong_input(int help)
{
	if (!help)
		print_error();
	else
		print_help();
	exit(1);
}
