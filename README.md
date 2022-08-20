# ft_printf - Because ft_putnbr() and ft_putstr() aren’t enough

### The goal of this project is pretty straightforward. You will recode printf(). You will mainly learn about using a variable number of arguments.
*Version : 9*

---

#### Mandatory part
##### Program name
* libftprintf.a
##### External functs. 
* malloc, free, write, va_start, va_arg, va_copy, va_end
##### Description
* Write a library that contains ft_printf(), a function that will mimic the original printf()

* Don’t implement the buffer management of the original printf().
* Your function has to handle the following conversions: cspdiuxX%
* Your function will be compared against the original printf().
* You must use the command ar to create your library. Using the libtool command is forbidden.
* Your libftprintf.a has to be created at the root of your repository.

#### Bonus part
* Manage any combination of the following flags: ’-0.’ and the field minimum width
under all conversions.
* Manage all the following flags: ’# +’ (Yes, one of them is a space)

---

보너스 함수는 기본 함수의 확장이므로, 보너스 함수만 만들었습니다.

이 밑은, 각 함수에 대해서, 간략하게 해당 함수의 코드와 함께 정리한 내용들입니다.
함수의 순서는 호출 순서입니다.
  
<details>
    <summary>int	ft_printf(const char *str, ...)</summary>
  
```c
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
```
* 인자로 받아온 스트링을 앞쪽부터 쭉 살펴보면서, '%'가 나타나면 다음 함수를 호출하고, 아니라면 해당 글자를 출력합니다.
- - -
</details>

<details>
    <summary>static int	parse_string(char **cur, va_list *vl)</summary>
  
```c
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
```
* '%'를 만났을 때, '%' 뒤의 인자들의 길이를 읽어와서 그만큼 건너뛰어야 하는데, 이 부분이 너무 길어져서 분리했습니다.
- - -
</details>

<details>
    <summary>static int	parse_argument(char *c, va_list *vl, int *argu_len)</summary>
  
```c
enum	e_args
{
	ARG_LJUSTIFY = 1 << 1,
	ARG_ZEROFILL = 1 << 2,
	ARG_SHARP = 1 << 3,
	ARG_PLUS = 1 << 4,
	ARG_SPACE = 1 << 5,
	ARG_PRECISION = 1 << 6,
	ARG_CAPITAL = 1 << 7,
	ARG_UNSIGNED = 1 << 8,
	FLAG_NEGATIVE = 1 << 9,
	FLAG_STRING = 1 << 10
};

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

```
* flag들을 읽어와서, 존재하는 flag가 있으면 체크해둡니다.
* 코드를 모두 짜고 떠올린거지만, 구조체를 이용하는 편이 설명하기에도, 이해하기에도 훨씬 수월했을거라 생각합니다.
* 중복될 수 없는 flag를 기준으로, 순서에 맞게 함수를 분리해서 읽어왔습니다. ![참고](https://cplusplus.com/reference/cstdio/printf/?kw=printf)
* 모두 읽고나면, 출력해야 하는 형식에 따라 flag를 수정한 뒤 다음 함수로 보냅니다.
- - -
</details>

<details>
    <summary>int	parse_flag1(char **c, int *argu_len)</summary>
  
```c
int	parse_flag1(char **c, int *argu_len)
{
	int	ret;

	ret = 0;
	if (**c == '#')
		ret = ARG_SHARP;
	else if (**c == '+')
		ret = ARG_PLUS;
	else if (**c == ' ')
		ret = ARG_SPACE;
	if (ret)
	{
		(*c)++;
		(*argu_len)++;
	}
	return (ret);
}
```
* 중복될 수 없는 '#', '+', ' ' flag들을 읽어옵니다.
- - -
</details>

<details>
    <summary>int	parse_flag2(char **c, int *width, va_list *vl, int *argu_len)</summary>
  
```c
static void	parse_width(char **c, int *width, va_list *vl, int *argu_len)
{
	if (**c == '*')
	{
		(*c)++;
		(*argu_len)++;
		*width = va_arg(*vl, int);
	}
	else if ('0' <= **c && **c <= '9')
		*width = ft_custom_atoi(c, argu_len);
}

int	parse_flag2(char **c, int *width, va_list *vl, int *argu_len)
{
	int	ret;

	ret = 0;
	*width = 0;
	if (**c == '-')
	{
		while (**c == '-')
		{
			(*c)++;
			(*argu_len)++;
		}
		ret = ARG_LJUSTIFY;
	}
	else if (**c == '0')
	{
		(*c)++;
		(*argu_len)++;
		ret = ARG_ZEROFILL;
	}
	parse_width(c, width, vl, argu_len);
	return (ret);
}
```
* 정렬이 필요한 flag들이 있는지 확인하고 읽어옵니다.
- - -
</details>

<details>
    <summary>int	parse_precision(char **c, int *precision, va_list *vl, int *argu_len)</summary>
  
```c
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

	ret = 0;
	*precision = 0;
	if (**c == '.')
		ret = ARG_PRECISION;
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
		else if ('0' <= **c && **c <= '9')
			*precision = ft_custom_atoi(c, argu_len);
	}
	return (ret);
}
```
* 정밀도가 필요한 flag가 있는지 확인하고 읽어옵니다.
- - -
</details>

<details>
    <summary>int	print_char(int flag, int width, va_list *vl)</summary>
  
```c
int	print_char(int flag, int width, va_list *vl)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * 2);
	if (!tmp)
		return (0);
	tmp[0] = va_arg(*vl, int);
	tmp[1] = '\0';
	return (write_result(flag & ARG_LJUSTIFY, tmp, __max(width, 1), 1));
}
```
* char는 정렬을 제외한 모든 flag가 무시되어도 문제 없습니다.
* 그러므로 해당 flag만 남긴 뒤, 너비값만 고려해서 다음 함수로 전달합니다.
- - -
</details>

<details>
    <summary>int	print_string(int flag, int width, int precision, va_list *vl)</summary>
  
```c
int	print_string(int flag, int width, int precision, va_list *vl)
{
	char		*tmp;
	long long	len;

	tmp = va_arg(*vl, char *);
	if (!tmp)
		tmp = "(null)";
	len = ft_strlen(tmp);
	if (flag & ARG_PRECISION && len > precision)
		len = precision;
	return (write_result((flag & ARG_LJUSTIFY) | FLAG_STRING, \
	tmp, __max(len, width), len));
}
```
* string은 정밀도 옵션이 존재할 떄, 주어진 정밀도보다 긴 부분은 잘립니다.
* 또한 주어진 string은 malloc한 것이 아니기에, FLAG_STRING flag를 같이 넘겨주어 나중에 free되는 것을 막습니다.
- - -
</details>

<details>
    <summary>int	print_pointer(int flag, int width, va_list *vl)</summary>
  
```c
int	print_pointer(int flag, int width, va_list *vl)
{
	char	*tmp;
	int		len;
	size_t	num;

	num = va_arg(*vl, size_t);
	len = get_length(16, num);
	tmp = (char *)malloc(sizeof(char) * len + 1);
	if (!tmp)
		return (0);
	custom_atoi_hex(flag, tmp, len, num);
	return (write_result((flag | ARG_SHARP), tmp, __max(len, width), len));
}
```
* 주어진 정수를 16진수로 바꾼 뒤, '0x' 부분이 같이 출력되도록 ARG_SHARP flag를 같이 넘겨줍니다.
- - -
</details>

<details>
    <summary>int	print_dec(int flag, int width, int precision, va_list *vl)</summary>
  
```c
int	print_dec(int flag, int width, int precision, va_list *vl)
{
	char		*tmp;
	int			len;
	int			mi;
	long long	num;

	num = va_arg(*vl, int);
	mi = 0;
	if (!(flag & ARG_UNSIGNED) && num < 0)
	{
		mi = 1;
		num = -num;
		flag &= ~(ARG_PLUS | ARG_SPACE);
	}
	if (flag & ARG_ZEROFILL && flag & ARG_PRECISION)
		flag &= ~ARG_ZEROFILL;
	len = __max(get_length(10, (unsigned int)num), precision);
	if (flag & ARG_PRECISION && !precision && !num)
		len = 0;
	tmp = (char *)malloc(sizeof(char) * len + 1);
	if (!tmp)
		return (0);
	custom_atoi_udec(tmp, len, num);
	return (write_result(flag | (mi * FLAG_NEGATIVE), \
	tmp, __max(len, width), len));
}
```
* 음수일 경우 양수로 바꾼 뒤, '-'를 같이 출력하도록 FLAG_NEGATIVE flag를 같이 넘겨줍니다.
* '0' flag와 '.' flag가 같이 사용될 경우, "   0001" 형태로 출력되는 것을 확인할 수 있습니다. 그러므로 두 flag가 동시에 사용된다면 FLAG_ZEROFILL flag를 제거해야 원하는 결과를 얻을 수 있습니다.
- - -
</details>

<details>
    <summary>int	print_hex(int flag, int width, int precision, va_list *vl)</summary>
  
```c
int	print_hex(int flag, int width, int precision, va_list *vl)
{
	char			*tmp;
	int				len;
	unsigned int	num;

	num = va_arg(*vl, unsigned int);
	if (!num && flag & ARG_SHARP)
		flag -= ARG_SHARP;
	if (flag & ARG_ZEROFILL && flag & ARG_PRECISION)
		flag &= ~ARG_ZEROFILL;
	len = __max(get_length(16, num), precision);
	if (flag & ARG_PRECISION && !precision && !num)
		len = 0;
	tmp = (char *)malloc(sizeof(char) * len + 1);
	if (!tmp)
		return (0);
	custom_atoi_hex(flag, tmp, len, num);
	return (write_result(flag, tmp, __max(len, width), len));
}
```
* 음수일 경우 양수로 바꾼 뒤, '-'를 같이 출력하도록 FLAG_NEGATIVE flag를 같이 넘겨줍니다.
* '0' flag와 '.' flag가 같이 사용될 경우, "   0001" 형태로 출력되는 것을 확인할 수 있습니다. 그러므로 두 flag가 동시에 사용된다면 FLAG_ZEROFILL flag를 제거해야 원하는 결과를 얻을 수 있습니다.
- - -
</details>

<details>
    <summary>int	write_result(int flag, char *str, int width, int slen)</summary>
  
```c
int	write_result(int flag, char *str, int width, int slen)
{
	int			ret;
	char		filler;
	long long	fill_size;

	fill_size = __max(0, width - slen - !!(flag & FLAG_NEGATIVE) \
	- 2 * !!(flag & ARG_SHARP) - !!(flag & ARG_PLUS || flag & ARG_SPACE));
	ret = fill_size;
	filler = ' ';
	if (flag & ARG_ZEROFILL)
	{
		filler = '0';
		if (flag & FLAG_NEGATIVE)
		{
			ret += write(1, "-", 1);
			flag &= ~FLAG_NEGATIVE;
		}
	}
	while (!(flag & ARG_LJUSTIFY) && fill_size)
		fill_size -= write(1, &filler, 1);
	ret += write_argument(flag, str, slen);
	while (fill_size)
		fill_size -= write(1, &filler, 1);
	if (!(flag & FLAG_STRING))
		free(str);
	return (ret);
}
```
* 주어진 너비값에서, 정밀도 옵션까지 처리되어 만들어진 str의 길이를 빼주고, '+', '#' 옵션등에 의해 출력될 글자의 개수를 빼 줍니다.
* 이 결과는 정렬을 위해 필요한 나머지 글자(filler)의 개수입니다.
* 좌측 정렬인지, 우측 정렬인지에 따라 filler를 출력하고, 미리 만들어둔 문자열을 출력합니다.
- - -
</details>

<details>
    <summary>static int	write_argument(int flag, char *str, int width)</summary>
  
```c
static int	write_argument(int flag, char *str, int width)
{
	int	ret;
	int	write_siz;

	ret = 0;
	if (flag & ARG_SHARP && flag & ARG_CAPITAL)
		ret += write(1, "0X", 2);
	else if (flag & ARG_SHARP)
		ret += write(1, "0x", 2);
	else if (flag & ARG_PLUS)
		ret += write(1, "+", 1);
	else if (flag & ARG_SPACE)
		ret += write(1, " ", 1);
	else if (flag & FLAG_NEGATIVE)
		ret += write(1, "-", 1);
	while (width)
	{
		write_siz = write(1, str, width);
		str += write_siz;
		ret += write_siz;
		width -= write_siz;
	}
	return (ret);
}

```
* flag에 의해 출력해야 하는 문자들과, 만들어 둔 문자열을 출력합니다.
- - -
</details>

[![Hits](https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2Fr4pidstart%2Fft_printf&count_bg=%23000000&title_bg=%23000000&icon=&icon_color=%23000000&title=hits&edge_flat=false)](https://hits.seeyoufarm.com)
