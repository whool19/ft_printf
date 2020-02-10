/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floats.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 20:00:17 by jterrell          #+#    #+#             */
/*   Updated: 2020/01/27 20:00:46 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		dbl(t_pf *pf)
{
	if (pf->num == -5.0 / 0)
	{
		write(1, "-inf", 4);
		pf->printed += 4;
		return (1);
	}
	else if (pf->num == 5.0 / 0)
	{
		write(1, "inf", 3);
		pf->printed += 3;
		return (1);
	}
	else if (pf->num == -LDBL_MIN && pf->precision == 0)
	{
		write(1, "-0", 2);
		pf->printed += 2;
		return (1);
	}
	return (0);
}

int		handle_float(t_pf *pf)
{
	if (ft_strequ(pf->size_flag, "\0") == 1 || (pf->printed > 0 &&\
	pf->size_flag == NULL) || (ft_strequ(pf->size_flag, "l") == 1))
		pf->num = va_arg(pf->ap, double);
	else if (ft_strequ(pf->size_flag, "L") == 1)
		pf->num = (long double)va_arg(pf->ap, long double);
	if (dbl(pf))
		return (pf->printed);
	else
		print_float(pf, pf->num);
	return (pf->printed);
}

int		sign(t_pf *pf, long double tmp, int len)
{
	if (pf->need_format == 0)
		pf->filling = ft_strjoinfree_both(spaces(' ', pf->width - len -
		pf->need_spase), pf->filling);
	if ((pf->need_spase == 1) && (tmp > 0) && (pf->need_sign == 0))
		pf->filling = ft_strjoinfree_both(pf->filling, ft_strdup(" "));
	if ((tmp < 0))
	{
		pf->filling = ft_strjoinfree_both(ft_strdup("-"), pf->filling);
		tmp = -tmp;
		return (-1);
	}
	else if (pf->need_sign == 1)
		pf->filling = ft_strjoinfree_both(ft_strdup("+"), pf->filling);
	return (1);
}

int		ft_length(long double num, int prec)
{
	if (prec >= 0)
		return (find_len_of_num((int)num) + prec);
	else
		return (find_len_of_num((int)num) + 6);
}
