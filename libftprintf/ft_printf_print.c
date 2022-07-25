/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 00:38:49 by tjo               #+#    #+#             */
/*   Updated: 2022/07/25 23:39:56 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	print_char(int flag, int width, va_list *vl)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * 2);
	tmp[0] = va_arg(*vl, int);
	tmp[1] = '\0';
	return (write_result(flag & 1 << 1, tmp, __max(1, width)));
}

int	print_string(int flag, int width, va_list *vl)
{
	return (write_result((flag & 1 << 1) | (1 << 8), \
	va_arg(*vl, char *), width));
}

int	print_pointer(int flag, int width, int precision, va_list *vl)
{
	char	*tmp;
	int		len;
	size_t	num;

	num = va_arg(*vl, size_t);
	len = get_length_ul(16, num);
	tmp = (char *)malloc(sizeof(char) * __max(len, width) + 1);
	if (!tmp)
		return (0);
	custom_atoi_hex(flag, tmp, __max(len, width), num);
	return (write_result((flag | (1 << 3)), tmp, max__(len, width));
}

int	print_dec(int flag, int width, int precision, va_list *vl)
{
	char		*tmp;
	int			len;
	long long	num;

	num = va_arg(*vl, int);
	if (flag & (1 << 7))
		len = get_length_ul(10, (size_t)num);
	else
		len = get_length(10, num);
	tmp = (char *)malloc(sizeof(char) * __max(len, precision) + 1);
	custom_atoi_dec(tmp, __max(len, width), num);
	return (write_result(flag & (1 << 2), tmp, __max(len, width)));
}

int	print_hex(int flag, int width, int precision, va_list *vl)
{
	char			*tmp;
	int				len;
	unsigned int	num;

	num = va_arg(*vl, unsigned int);
	len = get_length_ul(16, num);
	tmp = (char *)malloc(sizeof(char) * __max(len, precision) + 1);
	if (!tmp)
		return (0);
	custom_atoi_hex(flag, tmp, __max(len, precision), num);
	return (write_result(flag, tmp, width));
}
