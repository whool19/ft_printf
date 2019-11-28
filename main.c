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
		ft_parse_optionals();
	if ((test = ft_strchri(*p->str, "")))
		printf("\n\n", *p->str);
}

int 	main(void)
{
	int 	a = 3, b = 4, c = 5;
	printf("%d%d%d\n", a, b, c);
	ft_printf("hello  world %d !!");
	return (0);
}