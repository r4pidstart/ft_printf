/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 00:38:49 by tjo               #+#    #+#             */
/*   Updated: 2022/07/28 17:47:00 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	print_char(int flag, int width, va_list *vl)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * 2);
	tmp[0] = va_arg(*vl, int);
	tmp[1] = '\0';
	return (write_result(flag & 1 << 1, tmp, __max(width, 1)));
}

int	print_string(int flag, int width, va_list *vl)
{
	char	*tmp;

	tmp = va_arg(*vl, char *);
	if (!tmp)
		tmp = "(null)";
	return (write_result((flag & 1 << 1) | (1 << 8), \
	tmp, __max(ft_strlen(tmp), width)));
}

int	print_pointer(int flag, int width, va_list *vl)
{
	char	*tmp;
	int		len;
	size_t	num;

	num = va_arg(*vl, size_t);
	len = get_length_ul(16, num);
	tmp = (char *)malloc(sizeof(char) * len + 1);
	if (!tmp)
		return (0);
	custom_atoi_hex(flag, tmp, len, num);
	return (write_result((flag | (1 << 3)), tmp, width));
}

int	print_dec(int flag, int width, int precision, va_list *vl)
{
	char		*tmp;
	int			len;
	int			mi;
	int			number_len;
	long long	num;

	num = va_arg(*vl, int);
	mi = 0;
	if (!(flag & (1 << 7)) && num < 0)
	{
		mi = 1;
		num = -num;
	}
	if (flag & (1 << 7))
		number_len = get_length_ul(10, (unsigned int)num);
	else
		number_len = get_length(10, num);
	len = __max(number_len + mi, precision);
	tmp = (char *)malloc(sizeof(char) * len + 1 + mi);
	if (flag & (1 << 7))
		custom_atoi_udec(tmp, (unsigned int)len, num);
	else
		custom_atoi_dec(tmp, len, num);
	if (mi)
		tmp[len - number_len - 1] = '-';
	return (write_result(flag, tmp, width));
}

int	print_hex(int flag, int width, int precision, va_list *vl)
{
	char			*tmp;
	int				len;
	unsigned int	num;

	num = va_arg(*vl, unsigned int);
	len = __max(get_length_ul(16, num), precision);
	tmp = (char *)malloc(sizeof(char) * len + 1);
	if (!tmp)
		return (0);
	custom_atoi_hex(flag, tmp, len, num);
	return (write_result(flag, tmp, width));
}
