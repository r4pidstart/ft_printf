/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 00:53:23 by tjo               #+#    #+#             */
/*   Updated: 2022/07/28 19:08:01 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

// 1 -> -
// 2 -> 0
// 3 -> "0x"
// 4 -> '+'
// 5 -> ' '
// 8 -> do not free
// 9 -> argument is negative

static int	write_argument(int flag, char *str, int width)
{
	int	ret;

	ret = 0;
	if (flag & (1 << 3) && flag & (1 << 7))
		ret += write(1, "0X", 2);
	else if (flag & (1 << 3))
		ret += write(1, "0x", 2);
	else if (flag & (1 << 4))
		ret += write(1, "+", 1);
	else if (flag & (1 << 5))
		ret += write(1, " ", 1);
	else if (flag & (1 << 9))
		ret += write(1, "-", 1);
	while (width--)
	{
		write(1, str++, 1);
		ret++;
	}
	return (ret);
}

// the width is processed here
int	write_result(int flag, char *str, int width, int slen)
{
	int			ret;
	char		filler;
	long long	fill_size;

	ret = 0;
	filler = ' ';
	fill_size = width - slen - !!(flag & (1 << 9));
	fill_size -= (2 * !!(flag & (1 << 3)));
	fill_size -= !!((flag & (1 << 4)) || (flag & (1 << 5)));
	fill_size = __max(0, fill_size);
	if (flag & (1 << 2))
	{
		filler = '0';
		if (flag & (1 << 9))
		{
			ret += write(1, "-", 1);
			flag ^= (1 << 9);
		}
	}
	if (!(flag & (1 << 1)))
	{
		while (fill_size)
		{
			ret += write(1, &filler, 1);
			fill_size--;
		}	
	}
	ret += write_argument(flag, str, slen);
	while (fill_size--)
		ret += write(1, &filler, 1);
	if (!(flag & (1 << 8)))
		free(str);
	return (ret);
}
