/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 15:19:28 by jslave            #+#    #+#             */
/*   Updated: 2019/12/21 15:19:30 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*cut_string(char *str, int q)
{
	char *res;

	res = ft_memalloc(sizeof(char) * q + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, str, q);
	return (res);
}

void			handle_zero_prec(t_pf *pf)
{
	pf->filling = ft_strdup("");
	if (pf->type == '%')
	{
		pf->filling = ft_strnew(1);
		pf->filling[0] = '%';
	}
}

void			transform_str_precision(t_pf *pf)
{
	int		len;
	char	*zero;

	len = ft_strlen(pf->filling);
	if (pf->precision > len && (find_types(&pf->type, INT_TYPES)))
	{
		zero = ft_memalloc(pf->precision - len + 1);
		ft_memset(zero, '0', pf->precision - len);
		pf->filling = ft_strjoinfree_both(zero, pf->filling);
	}
	else if (pf->precision > 0 && pf->precision < len && pf->type == 's')
	{
		zero = cut_string(pf->filling, pf->precision);
		if (*zero)
		{
			ft_memdel((void **)&pf->filling);
			pf->filling = ft_strdup(zero);
			ft_memdel((void **)&zero);
		}
	}
	else if (pf->precision == 0)
		handle_zero_prec(pf);
}

void			print_char(t_pf *pf)
{
	int i;
	int len;

	len = ft_strlen(pf->str_empty);
	if (pf->width == 0)
		ft_putchar('\0');
	else
	{
		pf->printed += len - 1;
		if (pf->align_left == 1)
		{
			ft_putchar('\0');
			i = 1;
			while (pf->str_empty[i] != '\0')
				ft_putchar(pf->str_empty[i++]);
		}
		else
		{
			i = 0;
			while (i++ != (len - 1))
				ft_putchar(pf->str_empty[i]);
			ft_putchar('\0');
		}
	}
}

void			fill_and_print_string(t_pf *pf)
{
	int len;

	transform_str_precision(pf);
	len = ft_strlen(pf->filling);
	if (len == 0 && pf->type == 'c')
		print_char(pf);
	else if (pf->precision != -1 && (pf->width == 0 || pf->width < len))
	{
		ft_putstr(pf->filling);
		pf->printed += len;
	}
	else if (pf->width >= len && pf->precision != -1)
	{
		(pf->align_left == 1) ? (ft_memcpy(pf->str_empty, pf->filling, len))
		: (ft_memcpy((pf->str_empty + ft_strlen(pf->str_empty)) - len,
				pf->filling, len));
		ft_putstr(pf->str_empty);
		pf->printed += ft_strlen(pf->str_empty);
	}
	else if (ft_strlen(pf->str_empty) && pf->precision == -1)
	{
		ft_putstr(pf->str_empty);
		pf->printed += ft_strlen(pf->str_empty);
	}
}
