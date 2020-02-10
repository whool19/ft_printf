/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:58:58 by jslave            #+#    #+#             */
/*   Updated: 2020/02/08 18:59:06 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			turn_width_more_prec_uns(t_pf *pf, int len)
{
	if (ft_strlen(pf->str_empty) > (size_t)len)
	{
		if (pf->align_left != 1)
			ft_memcpy(&pf->str_empty[pf->width - len], pf->filling, len);
		else
			ft_memcpy(pf->str_empty, pf->filling, len);
		ft_memdel((void **)&pf->filling);
		pf->filling = ft_strdup(pf->str_empty);
	}
}

void		handle_int_space_2_uns(t_pf *pf, unsigned long long int num, int len)
{
	if (pf->filling[0] == '0')
	{
		if (num != 0)
			pf->filling[0] = ' ';
		else
			ft_str_overlap_copy(pf->filling);
		pf->filling[0] = ' ';
		if (num == 0 && pf->width == 1)
			pf->filling = ft_strjoinfree_both(pf->filling, ft_strdup("0"));
	}
	else if (len >= pf->width)
		pf->filling = ft_strjoinfree_both(ft_strdup(" "), pf->filling);
	else
	{
		if (pf->width > len && pf->align_left == 1)
			ft_str_overlap_copy(pf->filling);
	}
}

void			handle_int_precision_uns(t_pf *pf, unsigned long long int num)
{
	char		*zero;
	int			len;

	len = ft_strlen(pf->filling);
	if (pf->precision > len)
	{
		zero = fill_zero_string(pf, len, num);
		pf->filling = ft_strjoinfree_both(zero, pf->filling);
	}
}

void			handle_int_width_uns(t_pf *pf)
{
	int len;

	len = ft_strlen(pf->filling);
	if (pf->width > len)
	{
		fill_empty_str_pos_num(pf, len);
		ft_memdel((void **)&pf->filling);
		pf->filling = ft_strdup(pf->str_empty);
	}
}

void			handle_int_width_and_precision_uns(t_pf *pf, unsigned long long int num)
{
	int len;

	handle_int_precision_uns(pf, num);
	len = ft_strlen(pf->filling);
	if (pf->width > pf->precision)
	{
		if (pf->precision != 0 && pf->precision != -1)
			turn_width_more_prec_uns(pf, len);
		else if (pf->precision <= 0 && num == 0)
		{
			ft_memdel((void **)&pf->filling);
			pf->filling = ft_strdup(pf->str_empty);
			if (pf->need_sign == 1 && pf->align_left != 1)
				pf->filling[ft_strlen(pf->filling) - 1] = '+';
			else if (pf->need_sign == 1 && pf->align_left == 1)
				pf->filling[0] = '+';
			pf->need_sign = 0;
		}
	}
	else
		handle_int_precision_uns(pf, num);
}

void			handle_int_space_uns(t_pf *pf, unsigned long long int num)
{
	int len;

	if (handle_max_and_min_long_long(pf) == 1)
		return ;
	len = find_len_of_num((int)num);
	if (pf->precision <= 0 && pf->width == 0 && num)
		pf->filling = ft_strjoinfree_both(ft_strdup(" "), pf->filling);
	else if (pf->precision <= 0 && pf->width > 0 && num)
		handle_int_space_2_uns(pf, num, len);
	else if (pf->width > pf->precision && num)
	{
		if (pf->align_left != 1)
		{
			if (pf->filling[0] == '0')
				pf->filling[0] = ' ';
		}
		else
			ft_str_overlap_copy(pf->filling);
	}
	else
		pf->filling = ft_strjoinfree_both(ft_strdup(" "), pf->filling);
}

void			print_int_uns(t_pf *pf, unsigned long long int num)
{
	if (pf->precision >= 0 && pf->width > 0)
		handle_int_width_and_precision_uns(pf, num);
	else if (pf->precision < 0)
	{
		if (pf->width > 1)
			handle_int_width_uns(pf);
		else
			handle_int_precision_uns(pf, num);
	}
	else if (pf->precision > 0 && pf->precision > (int)find_len_of_num(num))
		handle_int_precision_uns(pf, num);
	if (pf->need_spase == 1 && pf->need_sign != 1)
		handle_int_space_uns(pf, num);
	ft_putstr(pf->filling);
	pf->printed += ft_strlen(pf->filling);
}


