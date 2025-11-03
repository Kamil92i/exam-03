/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kberraho <kberraho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:41:18 by kberraho          #+#    #+#             */
/*   Updated: 2025/08/05 11:15:35 by kberraho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	match_space(FILE *f)
{
	int	c;

	c = fgetc(f);
	while (c != EOF && isspace(c))
		c = fgetc(f);
	if (c == EOF)
		return (-1);
	ungetc(c, f);
	return (1);
}

int	match_char(FILE *f, char c)
{
	int	input;

	input = fgetc(f);
	if (input == EOF)
		return (-1);
	if (input == c)
		return (1);
	ungetc(input, f);
	return (0);
}

int	scan_char(FILE *f, va_list ap)
{
	int		c;
	char	*ptr;

	c = fgetc(f);
	if (c == EOF)
		return (-1);
	ptr = va_arg(ap, char *);
	*ptr = c;
	return (1);
}

int	scan_int(FILE *f, va_list ap)
{
	int	sign;
	int	digit_scaned;
	int	c;
	int	r;
	int	*ptr;

	sign = 1;
	digit_scaned = 0;
	c = fgetc(f);
	r = 0;
	if (c == '+' || c == '-')
	{
		if (c == '-')
			sign = -1;
		c = fgetc(f);
	}
	while (c != EOF && isdigit(c))
	{
		r = r * 10 + (c - '0');
		digit_scaned++;
		c = fgetc(f);
	}
	if (c != EOF)
		ungetc(c, f);
	if (digit_scaned == 0)
		return (0);
	ptr = va_arg(ap, int *);
	*ptr = r * sign;
	return (1);
}

int	scan_string(FILE *f, va_list ap)
{
	char	*str;
	int		c;
	int		chars_scaned;

	str = va_arg(ap, char *);
	c = fgetc(f);
	chars_scaned = 0;
	while (c != EOF && !isspace(c))
	{
		str[chars_scaned] = c;
		chars_scaned++;
		c = fgetc(f);
	}
	if (c != EOF)
		ungetc(c, f);
	str[chars_scaned] = '\0';
	if (chars_scaned == 0)
		return (0);
	return (1);
}

int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
	case 'c':
		return (scan_char(f, ap));
	case 'd':
		return (scan_int(f, ap));
	case 's':
		return (scan_string(f, ap));
	default:
		return (-1);
	}
}

int	ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int	nconv;
	int	ret;

	nconv = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			ret = match_conv(f, &format, ap);
			if (ret == -1)
			{
				return ((nconv == 0) ? -1 : nconv);
			}
			else if (ret == 0)
			{
				return nconv;
			}
			else
			{
				nconv++;
			}
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
			{
				return (nconv == 0) ? -1 : nconv;
			}
		}
		else
		{
			ret = match_char(f, *format);
			if (ret == -1)
			{
				return (nconv == 0) ? -1 : nconv;
			}
			else if (ret == 0)
			{
				return nconv;
			}
		}
		format++;
	}
	if (ferror(f))
	{
		return -1;
	}
	return nconv;
}

int	ft_scanf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}
