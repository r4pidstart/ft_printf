/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 21:56:30 by tjo               #+#    #+#             */
/*   Updated: 2022/07/25 23:42:51 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

/* cspdiuxX% */
static int	parse_argument(char *c, va_list *vl)
{
	int	flag;
	int	width;
	int	precision;

	flag = 0;
	flag ^= parse_flag1(&c);
	flag ^= parse_flag2(&c, &width, vl);
	flag ^= parse_precision(&c, &precision, vl);
	if (*c == 'c')
		return (print_char(flag, width, vl));
	else if (*c == 's')
		return (print_string(flag, width, vl));
	else if (*c == 'p')
		return (print_pointer(flag, width, vl));
	else if (*c == 'd' || *c == 'i' || *c == 'u')
		return (print_dec(flag | (*c == 'u') << 7, width, precision, vl));
	else if (*c == 'x' || *c == 'X')
		return (print_hex(flag | (*c == 'X') << 7, width, precision, vl));
	else if (*c == '%')
		return (write(1, "%", 1));
	else
		return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	vl;
	char	*cur;
	int		ret;
	int		cnt;

	va_start(vl, str);
	cnt = 0;
	cur = (char *)str;
	while (*cur)
	{
		if (*cur == '%')
		{
			ret = parse_argument(++cur, &vl);
			cnt += ret;
			cur++;
		}
		else
		{
			ret = write(1, cur++, 1);
			cnt++;
		}
		if (!ret)
			return (0);
	}
	va_end(vl);
	return (cnt);
}
