/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floats_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:30:22 by jslave            #+#    #+#             */
/*   Updated: 2020/01/28 12:30:35 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printf_fill(t_pf *pf, long double tmp, int len)
{
	if (pf->flag >= 0)
	{
		if (pf->precision > 308)
			pf->filling = ft_strjoinfree_both(pf->filling,\
			ft_ftos_sec(ft_round(tmp, pf->precision), pf->precision));
		else
			pf->filling = ft_strjoinfree_both(pf->filling,\
			ft_ftos_sec(ft_round(tmp,\
			ft_power(0.1, pf->precision)), pf->precision));
	}
	if (pf->flag == -2)
	{
		pf->filling = ft_strjoinfree_both(pf->filling, spaces('.', 1));
		pf->filling = ft_strjoinfree_both(pf->filling, spaces('0', 6));
	}
	if (pf->need_format == 1)
		pf->filling = ft_strjoinfree_both(pf->filling, spaces(' ',\
		pf->width - len - pf->need_spase));
	if (pf->need_format == 1 && pf->precision == 0)
		pf->filling = ft_strjoinfree_both(pf->filling, spaces('.', 1));
}

void	printf_float_2(long double tmp, int len, t_pf *pf)
{
	unsigned long long	left;
	char				*src;
	long double			tmp1;

	tmp1 = tmp;
	tmp1 *= sign(pf, tmp, len);
	left = (unsigned long long)tmp1;
	tmp1 -= left;
	if (pf->flag == 1 && tmp1 > 0.5)
		left -= -1;
	if (tmp1 > 0.9999995 && pf->flag == 0 && pf->precision == 6)
		left -= -1;
	src = ft_itoa_long_long_uns(left);
	pf->filling = ft_strjoinfree_both(pf->filling, src);
	printf_fill(pf, tmp1, len);
}

void	sign_2(t_pf *pf)
{
	if (pf->num < 0 && pf->zero_filling == 0)
	{
		pf->filling = ft_strjoinfree_both(ft_strdup("-"), pf->filling);
		pf->flag = 1;
	}
	if (pf->need_sign == 1 && pf->num > 0 && pf->zero_filling == 0)
	{
		pf->filling = ft_strjoinfree_both(ft_strdup("+"), pf->filling);
		pf->flag = 1;
	}
	if ((int)ft_strlen(pf->filling) != pf->width)
		if (pf->zero_filling == 1 && pf->align_left == 0 && pf->need_sign == 1)
		{
			pf->filling = ft_strjoinfree_both(spaces('0',\
			pf->width - (int)ft_strlen(pf->filling) - pf->need_spase\
			- pf->need_sign * (pf->num > 0) - (pf->num < 0)), pf->filling);
		}
	if (pf->zero_filling == 1 && pf->align_left == 0 && pf->need_sign != 1)
	{
		pf->filling = ft_strjoinfree_both(spaces('0',\
		pf->width - (int)ft_strlen(pf->filling) - pf->need_spase *\
		(pf->num > 0) - pf->zero_filling * (pf->num < 0)), pf->filling);
	}
}

void	printf_fill_4(t_pf *pf)
{
	if (pf->align_left != 1 && pf->need_sign != pf->need_spase &&\
	pf->need_sign == 1 && pf->num > 0)
		pf->filling = ft_strjoinfree_both(spaces(' ', pf->width -\
		(int)ft_strlen(pf->filling) - pf->need_spase - pf->need_sign *\
		(pf->num > 0) * pf->zero_filling), pf->filling);
	else if (pf->align_left != 1 && pf->need_sign != pf->need_spase &&\
	pf->need_sign == 1 && pf->num < 0 && pf->zero_filling == 0)
		pf->filling = ft_strjoinfree_both(spaces(' ', pf->width -\
		(int)ft_strlen(pf->filling) - pf->need_spase), pf->filling);
	else if (pf->align_left != 1 && pf->need_sign != pf->need_spase &&\
	pf->need_sign == 1 && pf->num < 0 && pf->zero_filling == 1)
		pf->filling = ft_strjoinfree_both(spaces(' ', pf->width -\
		(int)ft_strlen(pf->filling) - pf->need_spase - 1), pf->filling);
	else if (pf->align_left != 1 && pf->need_sign == pf->need_spase &&\
	pf->need_sign == 0 && pf->num > 0)
		pf->filling = ft_strjoinfree_both(spaces(' ', pf->width -\
		(int)ft_strlen(pf->filling)), pf->filling);
	else if (pf->align_left != 1 && pf->need_sign == pf->need_spase &&\
	pf->need_sign == 0 && pf->num < 0)
		pf->filling = ft_strjoinfree_both(spaces(' ',\
		(pf->width - (int)ft_strlen(pf->filling) - (pf->zero_filling *\
		ft_if_in_str(pf->filling, '-') | pf->zero_filling))), pf->filling);
}
