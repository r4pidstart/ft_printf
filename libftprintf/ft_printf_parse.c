/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 00:12:47 by tjo               #+#    #+#             */
/*   Updated: 2022/07/28 17:39:17 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

static int	ft_custom_atoi(char **c, int *argu_len)
{
	int			sign;
	long long	ret;

	sign = 1;
	ret = 0;
	if (**c == '+' || **c == '-')
	{
		if (**c == '-')
			sign = -1;
		(*c)++;
	}
	while ('0' <= **c && **c <= '9')
	{
		ret = ret * 10 + (**c) - '0';
		(*c)++;
		(*argu_len)++;
	}
	return (ret * sign);
}

int	parse_precision(char **c, int *precision, va_list *vl, int *argu_len)
{
	int	ret;

	*precision = 0;
	if (**c == '.')
		ret = 1 << 6;
	else
		ret = 0;
	if (ret)
	{
		(*c)++;
		(*argu_len)++;
		if (**c == '*')
		{
			*precision = va_arg(*vl, int);
			(*c)++;
			(*argu_len)++;
		}
		else
			*precision = ft_custom_atoi(c, argu_len);
	}
	return (ret);
}

int	parse_flag2(char **c, int *width, va_list *vl, int *argu_len)
{
	int	ret;

	*width = 0;
	if (**c == '-')
		ret = 1 << 1;
	else if (**c == '0')
		ret = 1 << 2;
	else
		ret = 0;
	if (ret)
	{
		(*c)++;
		(*argu_len)++;
	}
	if (**c == '*')
	{
		*width = va_arg(*vl, int);
		(*c)++;
		(*argu_len)++;
	}
	else
		*width = ft_custom_atoi(c, argu_len);
	return (ret);
}

int	parse_flag1(char **c, int *argu_len)
{
	int	ret;

	if (**c == '#')
		ret = 1 << 3;
	else if (**c == '+')
		ret = 1 << 4;
	else if (**c == ' ')
		ret = 1 << 5;
	else
		ret = 0;
	if (ret)
	{
		(*c)++;
		(*argu_len)++;
	}
	return (ret);
}
