/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 00:38:49 by tjo               #+#    #+#             */
/*   Updated: 2022/07/26 00:08:32 by tjo              ###   ########.fr       */
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
	char	*tmp;

	tmp = va_arg(*vl, char *);
	return (write_result((flag & 1 << 1) | (1 << 8), \
	tmp, __max(ft_strlen(tmp), width)));
}

int	print_pointer(int flag, int width, va_list *vl)
{
	char	*tmp;
	int		len;
	size_t	num;

	num = va_arg(*vl, size_t);
	len = __max(get_length_ul(16, num), width);
	tmp = (char *)malloc(sizeof(char) * len + 1);
	if (!tmp)
		return (0);
	custom_atoi_hex(flag, tmp, len, num);
	return (write_result((flag | (1 << 3)), tmp, len));
}

int	print_dec(int flag, int width, int precision, va_list *vl)
{
	char		*tmp;
	int			len;
	long long	num;

	num = va_arg(*vl, int);
	if (flag & (1 << 7))
		len = __max(__max(get_length_ul(10, (size_t)num), precision), width);
	else
		len = __max(__max(get_length(10, num), precision), width);
	tmp = (char *)malloc(sizeof(char) * len + 1);
	custom_atoi_dec(tmp, len, num);
	return (write_result(flag & (1 << 2), tmp, len));
}

int	print_hex(int flag, int width, int precision, va_list *vl)
{
	char			*tmp;
	int				len;
	unsigned int	num;

	num = va_arg(*vl, unsigned int);
	len = __max(__max(get_length_ul(16, num), width), precision);
	tmp = (char *)malloc(sizeof(char) * len + 1);
	if (!tmp)
		return (0);
	custom_atoi_hex(flag, tmp, len, num);
	return (write_result(flag, tmp, len));
}
