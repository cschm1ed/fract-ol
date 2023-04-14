/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_no_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:59:06 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/14 23:52:50 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	party_shift(t_ui *ui);
static void	julia_shift(t_ui *ui);

/**
 * handle_no_event - Handles the no-event loop for the fractal viewer
 * @ui: pointer to the user interface structure
 *
 * Updates the fractal view if any changes are made, such as shifts or party
 * mode changes. Redraws the fractal if the redraw flag is set.
 * Returns 0 on success.
 */

int	handle_no_event(t_ui *ui)
{
	t_this	*this;

	this = &ui->this;
	if (ui->shift)
		julia_shift(ui);
	if (ui->party)
		party_shift(ui);
	if (ui->redraw)
	{
		this->rd.x = this->upper_bounds.x - this->lower_bounds.x;
		this->rd.y = this->upper_bounds.y - this->lower_bounds.y;
		this->pd.x = this->rd.x / ui->width;
		this->pd.y = this->rd.y / ui->height;
		draw_fractal(ui);
		mlx_put_image_to_window(ui->mlx, ui->win, ui->img, 0, 0);
		ui->redraw = 0;
	}
	return (0);
}

/**
 * party_shift - Adjusts the color shifts in party mode
 * @ui: pointer to the user interface structure
 *
 * Updates the color shifts for the fractal in party mode, and sets the redraw
 * flag to update the view.
 */

static void	party_shift(t_ui *ui)
{
	t_this	*this;

	this = &ui->this;
	this->rs += PARTY_RATE;
	this->bs += PARTY_RATE;
	this->gs += PARTY_RATE;
	ui->redraw = 1;
}

/**
 * julia_shift - Adjusts the Julia constants based on the current shift
 * @ui: pointer to the user interface structure
 *
 * Updates the Julia constants based on the current shift value, and sets the
 * redraw flag to update the view if necessary.
 */

static void	julia_shift(t_ui *ui)
{
	t_complex	*cons;

	cons = &ui->this.julia_constants;
	if (ui->shift == 1)
		cons->x += SHIFT_RATE * (cons->x < 2);
	else if (ui->shift == -1)
		cons->x -= SHIFT_RATE * (cons->x > -2);
	else if (ui->shift == 2)
		cons->y += SHIFT_RATE * (cons->y < 2);
	else if (ui->shift == -2)
		cons->y -= SHIFT_RATE * (cons->x > -2);
	if (cons->x < 2 && cons->x > -2
		&& cons->y < 2 && cons->y > -2)
		ui->redraw = 1;
}
