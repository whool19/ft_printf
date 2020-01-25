
#include "ft_printf.h"

size_t		find_len(long long int n)
{
	int len;

	len = 0;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	if (n > 0 && n < 10)
		return (len + 1);
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

void			reverse(char *src, long long int num)
{
	size_t	i;
	size_t	j;
	char	c;

	i = 0;
	j = find_len(num) - 1;
	if (j == 0)
		return ;
	while (i <= j)
	{
		c = src[i];
		src[i] = src[j];
		src[j] = c      ;
		i++;
		j--;
	}
}

static char			*check_validity_ll(long long int n)
{
	long long int		min;
	char	*res;
	long long int		max;

	min = LLONG_MIN;
	max = LLONG_MAX;
	res = NULL;
	if (n <= min)
		return (res = ft_strdup("-9223372036854775808"));
	if (n < min)
		return (res);
	if (n == 0)
	{
		res = ft_strdup("0");
		return (res);
	}
	if ((n > min && n < 0) || (n > 0 && n <= max))
		res = ft_strnew(find_len(n));
	return (res);
}

static char			*check_validity(long long int n)
{
    long long int		min;
    char	*res;
    long long int		max;

    min = LLONG_MIN;
    max = LLONG_MAX;
    res = NULL;
    if (n <= min)
        return (res = ft_strdup("−2147483648"));
    if (n < min)
        return (res);
    if (n == 0)
    {
        res = ft_strdup("0");
        return (res);
    }
    if ((n > min && n < 0) || (n > 0 && n <= max))
        res = ft_strnew(find_len(n));
    return (res);
}

char				*ft_itoa_long_long(long long int n) {
    char *res;
    size_t i;
    long long int sign;
    size_t len;

    res = check_validity_ll(n);
    i = 0;
    len = find_len(n);
    if (res && n != LLONG_MIN && n != 0) {
        if ((sign = n) < 0) {
            res[i + len - 1] = '-';
            n = -n;
            len--;
        }
        while (i < len) {
            res[i++] = n % 10 + '0';
            n /= 10;
        }
        reverse(res, sign);
    }
    return (res);
}

char				*ft_itoa_long_long_uns(unsigned long long int n)
{
    char *res;
    size_t i;
    size_t len;

    res = check_validity(n);
    i = 0;
    len = find_len(n);
    if (res && n != 0) {
        while (i < len) {
            res[i++] = n % 10 + '0';
            n /= 10;
        }
        reverse(res, 1);
    }
    return (res);
}

long long  int		ft_return(unsigned long long int res, long long int neg)
{
    if (res >= 9223372036854775807 && neg == 1)
        return (-1);
    if (res >= 9223372036854775807 && neg == -1)
        return (0);
    return (res * neg);
}

long long int				ft_atoi_long_long(const char *str)
{
    int				i;
    long long int	result;
    long long int	neg;

    result = 0;
    i = 0;
    neg = 1;
    while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            neg = -1;
        i++;
    }
    while (str[i] > 47 && str[i] < 58)
    {
        result = result * 10 + (str[i] - 48);
        i++;
    }
    return (ft_return(result, neg));
}

unsigned long long int				ft_atoi_long_long_uns(const char *str)
{
    int				i;
    unsigned long long int	result;
    long long int	neg;

    result = 0;
    i = 0;
    neg = 1;
    while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            neg = -1;
        i++;
    }
    while (str[i] > 47 && str[i] < 58)
    {
        result = result * 10 + (str[i] - 48);
        i++;
    }
    return (ft_return(result, neg));
}

