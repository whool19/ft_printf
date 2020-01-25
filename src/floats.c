/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floats.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 16:19:07 by jslave            #+#    #+#             */
/*   Updated: 2019/12/26 16:19:09 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <float.h>

int     ft_if_in_str(char *s1, char s2)
{
    int     i;

    i = 0;
    while (s1[i])
    {
        if (s1[i] == s2)
            return (1);
        i++;
    }
    return (0);
}

double		ft_power(double nb, double power)
{
    if (power < 0.0)
        return (0);
    if (power == 0.0)
        return (1);
    return (nb * ft_power(nb, power - 1));
}

static char    *spaces(char c, int n)
{
    char    *res;
    int     i;

    i = 0;
    res = ft_strnew(n);
    if (n == 1 && c == '.')
        return (".");
    if (n == 1 && c == '0')
        return ("0");
    if (n > 0 && n != 1)
        while (i < n)
        {
            res[i] = c;
            i++;
        }
    else if (n == 1)
        return (" ");
    return (res);
}

char    *reverse_str(char *str)
{
    size_t  i;
    size_t  len;

    i = 0;
    len = ft_strlen(str);
    while (i < len / 2 )
    {
        str[i] ^= str[len - i - 1] ^= str[i] ^= str[len - i - 1];
        i++;
    }
    return (str);
}

long double ft_round(long double x, long double acc)
{
    return ((x / acc + 0.5) * acc);
}

char    *ft_ftos_sec(long double num, int prec)
{
    int         i;
    long double tmp;
    char        *res;

    if (prec != 0)
        res = ft_strnew(prec + 2);
    else
        return (NULL);
    tmp = num;
    i = 0;
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

int     ft_length(long double num, int prec)
{
    if (prec >= 0)
        return (find_len((int)num) + prec);
    else
        return (find_len((int)num) + 6);
}

void    print_float(t_pf *pf, long double num)
{
    long double         tmp;
    unsigned long long  left;
    char                *src;
    int                 len;
    int                 flag;
    int                 n;

    flag = 0;
    n = 0;
    if (pf->precision == 0)
        flag = 1;
    if (pf->precision < 0)
    {
        pf->precision = 6;
    }
    tmp = num;
    len = ft_length(tmp, pf->precision);
    if (len > pf->width)
    {
        if (pf->need_format == 0)
            pf->filling = spaces(' ', pf->width - len - pf->need_spase);
        if ((pf->need_spase == 1)  && (tmp > 0) && (pf->need_sign == 0))
            pf->filling = ft_strjoinfree_s1(pf->filling, " ");
        if ((tmp < 0))
        {
            pf->filling = ft_strjoinfree_s2("-", pf->filling);
            tmp = -tmp;
        }
        else if (pf->need_sign == 1)
            pf->filling = ft_strjoinfree_s2("+", pf->filling);
        left = (int)tmp;
        tmp -= left;
        if (flag == 1 && tmp > 0.5)
            left -= -1;
        if ( ft_ftos_sec(ft_round(tmp, ft_power(0.1, pf->precision)), pf->precision) && ft_ftos_sec(ft_round(tmp, ft_power(0.1, pf->precision)), pf->precision)[1] == ':')
        {
            left -= -1;
            flag = -2;
        }
        src = ft_strnew(ft_strlen(ft_itoa_long_long(left)));
        src = ft_itoa_long_long_uns(left);
        src = reverse_str(src);
        pf->filling = ft_strjoinfree_s2(pf->filling, src);
        if ((flag == 1) && (pf->need_format == 1))
            pf->filling = ft_strjoin(pf->filling, ".");
        if (flag >= 0)
        {
            pf->filling = ft_strjoinfree_s1(pf->filling, ft_ftos_sec(ft_round(tmp, ft_power(0.1, pf->precision)), pf->precision));
        }
        if (flag == -2)
        {
            pf->filling = ft_strjoinfree_s1(pf->filling, spaces('.', 1));
            pf->filling = ft_strjoinfree_s1(pf->filling, spaces('0', 6));
        }
        if (pf->need_format == 1)
            pf->filling = ft_strjoinfree_s2(pf->filling, spaces(' ', pf->width - len - pf->need_spase));
    }
    else
    {
        if ((tmp < 0))
            tmp = -tmp;
        left = (int)tmp;
        tmp -= left;
        src = ft_strnew(ft_strlen(ft_itoa_long_long(left)));
        src = ft_itoa_long_long_uns(left);
        src = reverse_str(src);
        pf->filling = ft_strjoinfree_s2(pf->filling, src);
        if ((flag == 1) && (pf->need_format == 1))
            pf->filling = ft_strjoin(pf->filling, ".");
        flag = 0;
        pf->filling = ft_strjoinfree_s2(pf->filling, ft_ftos_sec(ft_round(tmp, ft_power(0.1, pf->precision)), pf->precision));
        if (num < 0 && pf->zero_filling == 0)
        {
            pf->filling = ft_strjoinfree_s2("-", pf->filling);
            flag = 1;
        }
        if (pf->need_sign == 1 && num > 0 && pf->zero_filling == 0)
        {
            pf->filling = ft_strjoinfree_s2("+", pf->filling);
            flag = 1;
        }
        if ((int)ft_strlen(pf->filling) != pf->width)
            if (pf->zero_filling == 1 && pf->align_left == 0 && pf->need_sign == 1)
            {
                pf->filling = ft_strjoinfree_s2(spaces('0', pf->width - (int)ft_strlen(pf->filling) - pf->need_spase - pf->need_sign * (num > 0) - (num < 0)), pf->filling);
            }
            if (pf->zero_filling == 1 && pf->align_left == 0 && pf->need_sign != 1)
            {
                pf->filling = ft_strjoinfree_s2(spaces('0', pf->width - (int)ft_strlen(pf->filling) - pf->need_spase * (num > 0) - pf->zero_filling * (num < 0)), pf->filling);
            }
            if (pf->align_left == 1 && pf->need_sign == 0)
            {
                pf->filling = ft_strjoinfree_s1(pf->filling,
                                                spaces(' ', pf->width - (int) ft_strlen(pf->filling) - (int)(pf->zero_filling * (num < 0)) - pf->need_spase * (num > 0)));
            }
               else if (pf->align_left == 1 && pf->need_sign == 1)
            {
                pf->filling = ft_strjoinfree_s1(pf->filling,
                                                spaces(' ', pf->width - (int) ft_strlen(pf->filling) - pf->need_sign * (num > 0) * pf->zero_filling - (num < 0) * !(flag)));
            }
            else if (pf->align_left != 1 && pf->need_sign != pf->need_spase && pf->need_sign == 0)
            {
                pf->filling = ft_strjoinfree_s2(spaces(' ', pf->width - (int)ft_strlen(pf->filling) - pf->need_spase * !(flag)), pf->filling);
            }
            else if (pf->align_left != 1 && pf->need_sign != pf->need_spase && pf->need_sign == 1 && num > 0)
            {
                pf->filling = ft_strjoinfree_s2(spaces(' ', pf->width - (int) ft_strlen(pf->filling) - pf->need_spase - pf->need_sign * (num > 0) * pf->zero_filling), pf->filling);
            }
            else if (pf->align_left != 1 && pf->need_sign != pf->need_spase && pf->need_sign == 1 && num < 0 && pf->zero_filling == 0)
                pf->filling = ft_strjoinfree_s2(spaces(' ', pf->width - (int) ft_strlen(pf->filling) - pf->need_spase), pf->filling);
            else if (pf->align_left != 1 && pf->need_sign != pf->need_spase && pf->need_sign == 1 && num < 0 && pf->zero_filling == 1)
                pf->filling = ft_strjoinfree_s2(spaces(' ', pf->width - (int) ft_strlen(pf->filling) - pf->need_spase - 1), pf->filling);
            else if (pf->align_left != 1 && pf->need_sign == pf->need_spase && pf->need_sign == 0 && num > 0)
                pf->filling = ft_strjoinfree_s2(spaces(' ', pf->width - (int)ft_strlen(pf->filling)), pf->filling);
            else if (pf->align_left != 1 && pf->need_sign == pf->need_spase && pf->need_sign == 0 && num < 0)
            {
                pf->filling = ft_strjoinfree_s2(spaces(' ', (pf->width - (int)ft_strlen(pf->filling) - (pf->zero_filling * ft_if_in_str(pf->filling, '-') | pf->zero_filling))), pf->filling);
            }
        if ((pf->need_spase == 1) && (num > 0) && (pf->need_sign == 0))
            pf->filling = ft_strjoinfree_s2(" ", pf->filling);
        if (pf->need_sign == 1 && num > 0 && pf->zero_filling == 1)
            pf->filling = ft_strjoinfree_s2("+", pf->filling);
        if (num < 0 && pf->zero_filling == 1)
            pf->filling = ft_strjoinfree_s2("-", pf->filling);
    }
    pf->printed += ft_strlen(pf->filling);
    ft_putstr(pf->filling);
}

int     handle_float(t_pf *pf)
{
    long double num;

    num = 0;
    if (pf->size_flag == NULL)
        num = va_arg(pf->ap, double);
    else if (ft_strequ(pf->size_flag, "L") == 1)
        num = (long double)va_arg(pf->ap, long double);
    if (num == -5.0/0)
    {
        write(1, "-inf", 4);
        pf->printed += 4;
    }
    else if (num == 5.0/0)
    {
        write(1, "inf", 3);
        pf->printed += 3;
    }
    else if ((long double)va_arg(pf->ap, long double) == -LDBL_MIN && pf->precision == 0)
    {
        write(1, "-0", 2);
        pf->printed += 2;
    }
    else
        print_float(pf, num);
    return (pf->printed);
};