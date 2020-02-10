/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ints.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 16:17:57 by jslave            #+#    #+#             */
/*   Updated: 2019/12/26 16:17:58 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			handle_int_sign_pos_prec(t_pf *pf)
{
	int i;

	i = 0;
	if (pf->filling[0] == '0' && pf->filling[pf->width - 1] == ' ')
		push_string_one_sign(pf);
	else if (pf->filling[0] == ' ')
	{
		while (pf->filling[i] != '\0' && pf->filling[i] == ' ')
			i++;
		pf->filling[i - 1] = '+';
	}
	else
	{
		if (pf->align_left != 1)
			pf->filling = ft_strjoinfree_both(ft_strdup("+"), pf->filling);
		else if (pf->filling[pf->width - 1] == ' ')
			push_string_one_sign(pf);
	}
}

static void		handle_int_sign_2(t_pf *pf)
{
	if (ft_strequ(" ", pf->filling) == 1)
		pf->filling[0] = '+';
	else
		pf->filling = ft_strjoinfree_both(ft_strdup("+"), pf->filling);
}

void			handle_int_sign(t_pf *pf, long long int num)
{
	int i;

	i = 0;
	if (pf->width > pf->precision && pf->width > 1)
	{
		if (pf->precision != -5 && pf->precision != -1)
			handle_int_sign_pos_prec(pf);
		else if (pf->width > (int)find_len_of_num(num))
		{
			if (pf->filling[0] == ' ' && pf->align_left != 1)
			{
				while (pf->filling[i] != '\0' && pf->filling[i] == ' ')
					i++;
				pf->filling[i - 1] = '+';
			}
			else if (pf->filling[0] != '0' && ft_isdigit(pf->filling[0]) == 1)
				push_string_one_sign(pf);
			else
				pf->filling[0] = '+';
		}
		else
			pf->filling = ft_strjoinfree_both(ft_strdup("+"), pf->filling);
	}
	else
		handle_int_sign_2(pf);
}



void			print_int(t_pf *pf, long long int num)
{
	if (pf->precision >= 0 && pf->width > 0)
		handle_int_width_and_precision(pf, num);
	else if (pf->precision < 0)
	{
		if (pf->width > 1)
			handle_int_width(pf, num);
		else
			handle_int_precision(pf, num);
	}
	else if (pf->precision > 0 && pf->precision > (int)find_len_of_num(num))
		handle_int_precision(pf, num);
	if (pf->need_sign == 1 && num >= 0)
		handle_int_sign(pf, num);
	if (pf->need_spase == 1 && pf->need_sign != 1)
		handle_int_space(pf, num);
	ft_putstr(pf->filling);
	pf->printed += ft_strlen(pf->filling);
}

int				handle_int(t_pf *pf)
{
	long long int num;

	num = 0;
	if (ft_strequ(pf->size_flag, "\0") == 1 || (pf->printed > 0
	&& pf->size_flag == NULL))
		num = va_arg(pf->ap, int);
	else if (ft_strequ(pf->size_flag, "hh") == 1)
		num = (signed char)va_arg(pf->ap, int);
	else if (ft_strequ(pf->size_flag, "h") == 1)
		num = (short)va_arg(pf->ap, int);
	else if (ft_strequ(pf->size_flag, "ll") == 1)
		num = (long long int)va_arg(pf->ap, long long int);
	else if (ft_strequ(pf->size_flag, "l") == 1)
		num = (long int)va_arg(pf->ap, long int);
	if (num == 0 && pf->width == 1 && (pf->precision == -1 ||
	pf->precision == 0))
		pf->filling = ft_strdup(" ");
	else if (num == 0 && (pf->precision == -1 || pf->precision == 0))
		pf->filling = ft_strdup("");
	else
		pf->filling = ft_itoa_long_long(num);
	print_int(pf, num);
	return (pf->printed);
}
