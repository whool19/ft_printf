/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ints.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:28:01 by jslave            #+#    #+#             */
/*   Updated: 2019/12/17 16:28:03 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		handle_pointer(t_pf *pf)
{
	unsigned long long int pnt;

	pnt = (unsigned long long int)va_arg(pf->ap, void *);//ширина и точность!!!!
	pf->filling = ft_itoa_base_unsigned(pnt, 16);
	pf->filling = ft_strjoinfree_s2("0x", pf->filling);//LEAK
	fill_and_print_string(pf);
    return (pf->printed);
}

int       handle_unsigned(t_pf *pf)
{
    unsigned long long int num;

    num = 0;
    if (pf->size_flag == NULL)
        num = (unsigned int)va_arg(pf->ap, unsigned int);
    else if (ft_strequ(pf->size_flag, "hh") == 1)
        num = (unsigned char)va_arg(pf->ap, unsigned int);
    else if (ft_strequ(pf->size_flag, "h") == 1)
        num = (unsigned short)va_arg(pf->ap, unsigned int);
    else if (ft_strequ(pf->size_flag, "ll") == 1)
        num = (unsigned long long int)va_arg(pf->ap, unsigned long long int);
    else if (ft_strequ(pf->size_flag, "l") == 1)
        num = (unsigned long int)va_arg(pf->ap,  unsigned long int);
    if (num == 0 && (pf->precision == -1 || pf->precision == 0))
        pf->filling = "";
    else
        pf->filling = ft_itoa_base_unsigned(num, 10);
    pf->need_spase = 0;
    pf->need_sign = 0;
    print_int_second_edition(pf, num);
    return (pf->printed);
}

int		handle_hex(t_pf *pf)
{
    unsigned long long int num;

    num = 0;
    if (pf->size_flag == NULL)
        num = (unsigned int)va_arg(pf->ap, unsigned int);
    else if (ft_strequ(pf->size_flag, "hh") == 1)
        num = (unsigned char)va_arg(pf->ap, unsigned int);
    else if (ft_strequ(pf->size_flag, "h") == 1)
        num = (unsigned short)va_arg(pf->ap, unsigned int);
    else if (ft_strequ(pf->size_flag, "ll") == 1)
        num = (unsigned long long int)va_arg(pf->ap, unsigned long long int);
    else if (ft_strequ(pf->size_flag, "l") == 1)
        num = (unsigned long int)va_arg(pf->ap,  unsigned long int);
    if (num == 0 && (pf->precision == -1 || pf->precision == 0))
        pf->filling = "";
    else
        pf->filling = ft_itoa_base_unsigned(num, 16);
    print_int_hex(pf);
    return (pf->printed);
};