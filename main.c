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
		ft_parse_optionals(*p, test);
	if ((test = ft_strchri(*p->str, "")))
		printf("\n\n", *p->str);
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

void	parse_type(t_printf *p, char test)
{
	if ()
}

int 	main(void)
{
	int 	a = 3, b = 4, c = 5;
	printf("%d%d%d\n", a, b, c);
	ft_printf("hello  world %d !!");
	return (0);
}