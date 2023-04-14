/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 08:44:01 by cschmied          #+#    #+#             */
/*   Updated: 2023/04/14 23:39:06 by cschmied         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

/**
 * ft_strlen - calculates the length of a string
 * @str: the input string
 * 
 * Calculates the length of the input string, not including the null terminator.
 * 
 * Return: the length of the input string
 */

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/**
 * ft_strisnum - checks if a given string contains only digits
 * @str: pointer to the input string
 *
 * This function iterates through the input string and checks if each
 * character is a digit. If it encounters a non-digit character, the
 * function returns 0 (false). If all characters are digits, it returns
 * 1 (true).
 *
 * Return: 1 if the string contains only digits, 0 otherwise
 */

int	ft_strisnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9' || str[i] == '.' || str[i] == '-')
			return (0);
		i++;
	}
	return (1);
}


/**
 * ft_putstr - prints a string to the standard output
 * @str: pointer to the null-terminated input string
 *
 * This function writes the input string to the standard output (file
 * descriptor 1) using the write() system call. The length of the string
 * is calculated using ft_strlen() function.
 */

void	ft_putstr(const char *str)
{
	write(1, str, ft_strlen(str));
}

/**
 * ft_strlower - converts a string to lowercase
 * @str: pointer to the null-terminated input string
 *
 * This function iterates through the input string and, for each uppercase
 * character, converts it to lowercase by adding 32. The input string is
 * modified in place.
 *
 * Return: pointer to the modified input string (lowercase)
 */

char	*ft_strlower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
	return (str);
}

/**
 * ft_strcmp - compares two strings lexicographically
 * @s1: pointer to the first null-terminated string
 * @s2: pointer to the second null-terminated string
 *
 * This function compares the input strings character by character. If a
 * difference is found or the end of one string is reached, it returns the
 * difference between the ASCII values of the current characters in s1 and s2.
 *
 * Return: 0 if equal, a positive or negative integer representing the difference
 */

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
