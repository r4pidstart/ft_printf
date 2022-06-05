/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 01:12:41 by tjo               #+#    #+#             */
/*   Updated: 2022/06/06 02:49:44 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	__max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	get_length(int base, long long n)
{
	int			ret;

	ret = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		ret++;
		n *= -1;
	}
	while (n)
	{
		ret++;
		n /= base;
	}
	return (ret);
}

int	get_length_ul(int base, size_t n)
{
	int	ret;

	ret = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		ret++;
		n /= base;
	}
	return (ret);
}

void	custom_atoi_dec(int flag, char *tmp, int len, long long num)
{
	long long	origin_num;

	origin_num = num;
	tmp[len] = '\0';
	while (len--)
	{
		if (!len && origin_num < 0)
			tmp[len] = '-';
		else if (!num)
			tmp[len] = '0';
		else
		{
			tmp[len] = num % 10 + '0';
			num /= 10;
		}
	}
	return (tmp);
}

void	custom_atoi_hex(int flag, char *tmp, int len, size_t num)
{
	tmp[len] = '\0';
	while (len--)
	{
		if (!num)
			tmp[len] = '0';
		else
		{
			if (num % 16 > 9 && flag & (1 << 7))
				tmp[len] = "ABCDEF"[num % 16 - 10];
			else if (num % 16 > 9)
				tmp[len] = "abcdef"[num % 16 - 10];
			else
				tmp[len] = num % 16 + '0';
			num /= 16;
		}
	}
	return (tmp);
}
