#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

# define F_SHARP		(1 << 0)
# define F_SPACE		(1 << 1)
# define F_PLUS			(1 << 2)
# define F_MINUS		(1 << 3)
# define F_ZERO			(1 << 4)
# define F_WILDCARD		(1 << 5)
# define F_UPCASE		(1 << 6)
# define F_SHORT		(1 << 7)
# define F_SHORT2		(1 << 8)
# define F_LONG			(1 << 9)
# define F_LONG2		(1 << 10)
# define F_INTMAX		(1 << 11)


typedef struct	s_printf
{
	va_list 	ap;
	int 		fd;
	char 		*buff;
	int 		len;
	char 		*str;
	short		mask;

}				t_printf;

int		ft_printf(const char *str, ...);
void	print_rand(t_printf *p);
void	printf_usual(t_printf *p);



#endif