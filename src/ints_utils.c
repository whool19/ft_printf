/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ints_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 21:20:31 by jslave            #+#    #+#             */
/*   Updated: 2020/01/08 21:20:34 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char        *fill_zero_string(t_pf *pf, int len, long long int num)
{
    char *zero;

    zero = NULL;

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

void        put_sign(t_pf *pf, long long int num)
{
    if (num < 0)
        pf->filling[0] = '-';
    else if (num == 0 && pf->need_sign == 1)
        pf->filling = ft_strjoinfree_s2("+", pf->filling);///FREEEE
}

void        fill_empty_str_neg_num(t_pf *pf, int len, long long num)
{
    pf->filling = ft_itoa_long_long(num*(-1));
    if (pf->align_left != 1)
    {
        ft_memcpy(&pf->str_empty[pf->width - len + 1], pf->filling,len);
        if (pf->zero_filling != 1)
            pf->str_empty[pf->width - len] = '-';
        else
            pf->str_empty[0] = '-';
    }
    else
    {
        ft_memcpy(&pf->str_empty[1], pf->filling, ft_strlen(pf->filling));
        pf->str_empty[0] = '-';
    }
}

void         fill_empty_str_pos_num(t_pf *pf, int len)
{
    if (pf->align_left != 1)
        ft_memcpy(&pf->str_empty[pf->width - len], pf->filling, len);
    else
        ft_memcpy(pf->str_empty, pf->filling, len);
}
