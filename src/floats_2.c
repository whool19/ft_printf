/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floats_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 20:00:17 by jterrell          #+#    #+#             */
/*   Updated: 2020/01/27 20:00:46 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_if_in_str(char *s1, char s2)
{
	int		i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == s2)
			return (1);
		i++;
	}
	return (0);
}

double			ft_power(double nb, double power)
{
	if (power < 0.0)
		return (0);
	if (power == 0.0)
		return (1);
	if (power > 308)
		return (1);
	return (nb * ft_power(nb, power - 1));
}

char			*spaces(char c, int n)
{
	char	*res;
	int		i;

	i = 0;
	if (n < 0)
		return (ft_strdup(""));
	res = ft_strnew(n);
	if (n == 1 && c == '.')
		return (ft_strdup("."));
	if (n == 1 && c == '0')
		return (ft_strdup("0"));
	if (n > 0 && n != 1)
		while (i < n)
		{
			res[i] = c;
			i++;
		}
	else if (n == 1)
		return (ft_strdup(" "));
	return (res);
}

long double		ft_round(long double x, long double acc)
{
	if (acc < 308)
		return ((x / acc + 0.5) * acc);
	else
		return (x);
}

char			*ft_ftos_sec(long double num, int prec)
{
	int			i;
	long double tmp;
	char		*res;

	if (prec != 0)
		res = ft_strnew(prec + 2);
	else
		return (NULL);
	tmp = num - (int)num;
	i = 0;
	if (prec > 0)
		res[0] = '.';
	while (i < prec)
	{
		res[i + 1] = (int)(tmp * 10) + 48;
		tmp *= 10;
		tmp -= (int)tmp;
		i++;
	}
	return (res);
}
