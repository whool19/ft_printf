/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:51:17 by jslave            #+#    #+#             */
/*   Updated: 2020/01/27 18:51:19 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			put_sign(t_pf *pf, long long int num)
{
	if (num < 0)
		pf->filling[0] = '-';
	else if (num == 0 && pf->need_sign == 1)
		pf->filling = ft_strjoinfree_both(ft_strdup("+"), pf->filling);
}

void			prec_less_width(t_pf *pf, long long int num, int len)
{
	char	*zero;
	int		diff;

	if (pf->align_left == 1)
		ft_memcpy(pf->str_empty, pf->filling, ft_strlen(pf->filling));
	else
	{
		if (pf->precision >= (int)find_len_of_num(num))
		{
			pf->filling = ft_itoa_long_long(num * -1);
			diff = pf->precision - ft_strlen(pf->filling);
			zero = ft_strnew(diff);
			ft_memset(zero, '0', diff);
			pf->filling = ft_strjoinfree_both(zero, pf->filling);
			pf->filling = ft_strjoinfree_both(ft_strdup("-"),
pf->filling);
			ft_memcpy(&pf->str_empty[pf->width - ft_strlen(pf->filling)],
pf->filling, ft_strlen(pf->filling));
		}
		else
			ft_memcpy(&pf->str_empty[pf->width - len], pf->filling,
ft_strlen(pf->filling));
	}
}

void			turn_width_more_prec(t_pf *pf, long long int num, int len)
{
	if (num < 0 && ft_strlen(pf->str_empty) > (size_t)find_len_of_num(num))
	{
		if (pf->precision < pf->width)
		{
			prec_less_width(pf, num, len);
			ft_memdel((void **)&pf->filling);
			pf->filling = ft_strdup(pf->str_empty);
		}
	}
	else if (ft_strlen(pf->str_empty) > (size_t)len)
	{
		if (pf->align_left != 1)
			ft_memcpy(&pf->str_empty[pf->width - len], pf->filling, len);
		else
			ft_memcpy(pf->str_empty, pf->filling, len);
		ft_memdel((void **)&pf->filling);
		pf->filling = ft_strdup(pf->str_empty);
	}
}

void			handle_int_precision(t_pf *pf, long long int num)//149
{
	char		*zero;
	int			len;

	len = ft_strlen(pf->filling);
	if (pf->precision > len)
	{
		if (num < 0)
		{
			pf->filling = ft_itoa_long_long(num * -1);
			len--;
		}
		zero = fill_zero_string(pf, len, num);
		pf->filling = ft_strjoinfree_both(zero, pf->filling);
		if (num < 0)
			put_sign(pf, num);
	}
}

void			push_string_one_sign(t_pf *pf)
{
	char *test;

	test = ft_strdup(pf->filling);
	ft_memcpy(&pf->filling[1], test, ft_strlen(test) - 1);
	ft_memdel((void **)&test);
	pf->filling[0] = '+';
}
