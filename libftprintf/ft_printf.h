/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 21:55:51 by tjo               #+#    #+#             */
/*   Updated: 2022/07/28 18:39:53 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include<stdarg.h>
# include<unistd.h>
# include<stdlib.h>

/* ft_printf_main.c */
int		ft_printf(const char *str, ...);

/* ft_printf_parse.c */
int		parse_flag1(char **c, int *argu_len);
int		parse_flag2(char **c, int *width, va_list *vl, int *argu_len);
int		parse_precision(char **c, int *precision, va_list *vl, int *argu_len);

/* ft_printf_print.c */
int		print_char(int flag, int width, va_list *vl);
int		print_string(int flag, int width, va_list *vl);
int		print_pointer(int flag, int width, va_list *vl);
int		print_dec(int flag, int width, int precision, va_list *vl);
int		print_hex(int flag, int width, int precision, va_list *vl);

/* ft_printf_utils.c */
int		__max(int a, int b);
size_t	ft_strlen(const char *s);
int		get_length(int base, long long n);
int		get_length_ul(int base, size_t n);
void	custom_atoi_dec(char *tmp, int len, long long n);
void	custom_atoi_udec(char *tmp, int len, unsigned int num);
void	custom_atoi_hex(int flag, char *tmp, int len, size_t n);

/* ft_printf_write.c */
int		write_result(int flag, char *str, int width, int slen);

#endif