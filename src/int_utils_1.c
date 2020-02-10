/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:37:25 by jslave            #+#    #+#             */
/*   Updated: 2020/02/07 16:37:30 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				handle_max_and_min_long_long(t_pf *pf)
{
	if (ft_strequ(pf->filling, "9223372036854775807") == 1)
	{
		pf->filling = ft_strdup(" 9223372036854775807");
		return (1);
	}
	else if (ft_strequ(pf->filling, "-9223372036854775807") == 1)
	{
		pf->filling = ft_strdup("-9223372036854775807");
		return (1);
	}
	return (0);
}

char			*fill_zero_string(t_pf *pf, int len, long long int num)
{
	char *zero;

	if (num < 0)
	{
		zero = ft_memalloc(sizeof(char) * (pf->precision - len + 2));
		ft_memset(zero, '0', pf->precision - len + 1);
	}
	else
	{
		zero = ft_memalloc(sizeof(char) * (pf->precision - len + 1));
		ft_memset(zero, '0', pf->precision - len);
	}
	return (zero);
}

int				check_llmax_and_llmin(t_pf *pf, long long int num)
{
	if (num == LLONG_MIN)
	{
		if (pf->zero_filling == 1 && pf->align_left != 1)
		{
			pf->filling = ft_strdup("9223372036854775808");
			pf->str_empty[0] = '-';
		}
		else
			pf->filling = ft_strdup("-9223372036854775808");
		ft_memcpy(pf->str_empty, pf->filling, ft_strlen(pf->filling));
		return (1);
	}
	if (num == LLONG_MAX)
	{
		pf->filling = ft_strdup("9223372036854775807");
		ft_memcpy(&pf->str_empty[1], pf->filling, ft_strlen(pf->filling));
		return (1);
	}
	return (0);
}

void			fill_empty_str_neg_num(t_pf *pf, int len, long long num)
{
	if (pf->align_left != 1 && pf->zero_filling != 1)
		ft_memcpy(&pf->str_empty[pf->width - len], pf->filling, len);
	else if (pf->zero_filling == 1 && pf->align_left != 1)
	{
		if (check_llmax_and_llmin(pf, num) == 1)
			return ;
		pf->filling = ft_itoa_long_long(num * (-1));
		if (pf->align_left != 1)
			ft_memcpy(&pf->str_empty[pf->width - len + 1], pf->filling, len);
		if (pf->str_empty[0] == '0')
			pf->str_empty[0] = '-';
		else
			pf->str_empty[pf->width - len] = '-';
	}
	else
	{
		if (check_llmax_and_llmin(pf, num) != 1)
		{
			pf->filling = ft_itoa_long_long(num * (-1));
			ft_memcpy(&pf->str_empty[1], pf->filling, ft_strlen(pf->filling));
			pf->str_empty[0] = '-';
		}
	}
}

void			fill_empty_str_pos_num(t_pf *pf, int len)
{
	if (pf->align_left != 1)
		ft_memcpy(&pf->str_empty[pf->width - len], pf->filling, len);
	else
		ft_memcpy(pf->str_empty, pf->filling, len);
}
