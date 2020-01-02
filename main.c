#include "ft_printf.h"
#include <stdio.h>
#include "libft/libft.h"

int		ft_printf(const char *str, ...)
{
	t_printf	p;

	ft_bzero(&p, sizeof(p));
	p.fd = 1;
	p.str = (char*)str;
	va_start(p.ap, str);
	while (*p.str != '\0')
	{
		if (*p.str == '%')
		{
			++p.str;
			if (!*p.str)
				break;
			print_rand(&p);
		}
		else
		{
				printf_usual(&p);
		}
		p.str++;
	}
	va_end(p.ap);
	return (p.len);
}

void	printf_usual(t_printf *p)
{
	//char	tmp;

	//tmp = *p->str;
	write(p->fd, p->str, 1);
	p->len++;
}

void	print_rand(t_printf *p)
{
	char	test;
	if ((test = ft_strchri(*p->str, "# +-0*")))
		parse_optionals();
	if (ft_isalpha(*p->str))
		ft_min_width(p);
	if (*p->str == '.')
		ft_min_accuracy(p);
	if ((test = ft_strchri(*p->str, "sdDifFcCoOuUbBxXSpnm{")))
		ft_final_print(p);
}

void	ft_final_print(t_printf *p)
{
	if (p->str == 's')
		(p->mask & F_LONG || p->mask & F_LONG2) ? pf_putwstr(p) : pf_putstr(p);
	else if (ft_strchr("dDi", p->str))
		pf_putnbr(p);
	else if (p->str == 'p')
		print_addres(p);
	else if (p->str == 'S')
		pf_putwstr(p);
}

void	parse_optionals(t_printf *p, char test)
{
	if (test == '#')
		p->mask |= F_SHARP;
	if (test == ' ')
		p->mask |= F_SPACE;
	if (test == '+')
		p->mask |= F_PLUS;
	if (test == '-')
		p->mask |= F_MINUS;
	if (test == '0')
		p->mask |= F_ZERO;
	if (test == '*')
		p->mask |= F_SHARP;
	p->str++;
}

void    ft_min_width(t_printf *p)
{
	while (ft_isalpha(*p->str))
	{
		p->min_width = *p->str - '0';
		p->str++;
		if (ft_isalpha(*p->str))
			p->min_width *= 10;
	}
}

void    ft_min_accuracy(t_printf *p)
{
	p->str++;
	while (ft_isalpha(*p->str))
	{
		p->min_accuracy = *p->str - '0';
		p->str++;
		if (ft_isalpha(*p->str))
			p->min_accuracy *= 10;
	}

}

int 	main(void)
{
	int 	a = 3, b = 4, c = 5;
	printf("%d%d%d\n", a, b, c);
	ft_printf("hello  world %d !!");
	return (0);
}