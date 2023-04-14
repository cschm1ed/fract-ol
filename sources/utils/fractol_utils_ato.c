/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils_ato.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 08:50:03 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/14 23:34:07 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

/**
 * ft_atoi - converts a string to an integer
 * @str: the input string to convert
 * 
 * Converts the initial portion of the input string to an integer.
 * The conversion stops when a non-digit character is encountered.
 * 
 * Return: the converted integer value
 */

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

/**
 * ft_atod - converts a string to a long double
 * @str: the input string to convert
 * 
 * Converts the initial portion of the input string to a long double.
 * The conversion stops when a non-digit character is encountered, except for
 * decimal points or commas which are treated as decimal separators.
 * 
 * Return: the converted long double value
 */

long double	ft_atod(const char *str)
{
	long double	result;
	long double	float_part;

	result = ft_atoi(str);
	while (*str != '.' && *str != ',' && *str != '\0')
		str++;
	float_part = ft_atoi(str + 1);
	while (float_part >= 1)
		float_part /= 10;
	return (result + float_part);
}
