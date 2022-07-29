/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 21:56:30 by tjo               #+#    #+#             */
/*   Updated: 2022/07/30 02:59:39 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

/* cspdiuxX% */
static int	parse_argument(char *c, va_list *vl, int *argu_len)
{
	int	flag;
	int	width;
	int	precision;

	flag = 0;
	while (*c == '#' || *c == '+' || *c == ' ')
		flag |= parse_flag1(&c, argu_len);
	flag |= parse_flag2(&c, &width, vl, argu_len);
	flag |= parse_precision(&c, &precision, vl, argu_len);
	if (*c == 'c')
		return (print_char(flag, width, vl));
	else if (*c == 's')
		return (print_string(flag, width, precision, vl));
	else if (*c == 'p')
		return (print_pointer(flag, width, vl));
	else if (*c == 'd' || *c == 'i' || *c == 'u')
		return (print_dec(flag | (*c == 'u') * ARG_UNSIGNED, \
		width, precision, vl));
	else if (*c == 'x' || *c == 'X')
		return (print_hex(flag | (*c == 'X') * ARG_CAPITAL, \
		width, precision, vl));
	else if (*c == '%')
		return (write(1, "%", 1));
	return (0);
}

static int	parse_string(char **cur, va_list *vl)
{
	int	argu_len;
	int	ret;

	ret = 0;
	argu_len = 1;
	ret = parse_argument(++(*cur), vl, &argu_len);
	(*cur) += argu_len;
	return (ret);
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
			cnt += parse_string(&cur, &vl);
		else
		{
			ret = write(1, cur++, 1);
			cnt++;
			if (!ret)
				return (0);
		}
	}
	va_end(vl);
	return (cnt);
}
