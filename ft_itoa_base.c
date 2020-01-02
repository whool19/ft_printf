#include "stdlib.h"
char	*ft_itoa_base(int value, int base)
{
	char *str;
	char *base_str = "0123456789ABCDEF";
	int len = 1;
	int nbr = value;
	if (base < 2 || base > 16)
		return NULL;
	if (value == 0)
		return ("0");
	while (nbr /= base)
		len++;
	nbr = value;
	if (nbr < 0)
	{
		if (base == 10)
			len++;
		nbr = -nbr;
	}
	if (!(str = malloc(sizeof(char)*len + 1)))
		return NULL;
	str[len] = '\0';
	while (nbr)
	{
		str[--len] = base_str[nbr % base];
		nbr /= base;
	}
	if (base == 10 && value < 0)
		str[0] = '-';
	return (str);
}