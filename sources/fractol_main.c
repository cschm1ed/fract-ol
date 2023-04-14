/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 09:23:05 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/14 23:50:18 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	loop_mlx(t_ui *ui);

/**
 * main - Entry point of the fractol application
 * @argc: number of command line arguments
 * @argv: array of command line arguments
 *
 * Initializes the user interface, processes command line arguments,
 * initializes fractal functions, and starts the main event loop.
 * Returns 0 on success.
 */

int	main(int argc, char **argv)
{
	t_ui	ui;

	errno = 0;
	if (argc == 1)
		wrong_input(0);
	if (!init_inputs(&ui, argv, argc))
		return (0);
	if (!ui_init(&ui, argv))
		return (0);
	this_init(&ui);
	loop_mlx(&ui);
	free(ui.mlx);
	return (0);
}

/**
 * loop_mlx - Runs the main event loop for the fractal viewer
 * @ui: pointer to the user interface structure
 *
 * Draws the fractal, sets up event hooks, and starts the mlx loop.
 */

void	loop_mlx(t_ui *ui)
{
	draw_fractal(ui);
	mlx_put_image_to_window(ui->mlx, ui->win, ui->img, 0, 0);
	mlx_key_hook(ui->win, &handle_keypress, ui);
	mlx_mouse_hook(ui->win, &handle_mouse, ui);
	mlx_loop_hook(ui->mlx, &handle_no_event, ui);
	mlx_hook(ui->win, 17, 0, &fractol_quit, ui);
	mlx_loop(ui->mlx);
}
