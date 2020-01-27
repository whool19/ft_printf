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
    tmp = num - (int)num;
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
        return (find_len_of_num((int)num) + prec);
    else
        return (find_len_of_num((int)num) + 6);
}

int    sign(t_pf *pf, long double tmp, int len)
{
    if (pf->need_format == 0)
        pf->filling = spaces(' ', pf->width - len - pf->need_spase);
    if ((pf->need_spase == 1)  && (tmp > 0) && (pf->need_sign == 0))
        pf->filling = ft_strjoinfree_s2(pf->filling, ft_strdup(" "));
    if ((tmp < 0))
    {
        pf->filling = ft_strjoinfree_s1(ft_strdup("-"), pf->filling);
        tmp = -tmp;
        return (-1);
    }
    else if (pf->need_sign == 1)
        pf->filling = ft_strjoinfree_s1(ft_strdup("+"), pf->filling);
    return (1);
}

void    printf_fill(t_pf *pf, long double tmp, int len)
{
    if ((pf->flag == 1) && (pf->need_format == 1))
        pf->filling = ft_strjoin(pf->filling, ".");
    if (pf->flag >= 0)
    {
        pf->filling = ft_strjoinfree_s1(pf->filling, ft_ftos_sec(ft_round(tmp, ft_power(0.1, pf->precision)), pf->precision));
    }
    if (pf->flag == -2)
    {
        pf->filling = ft_strjoinfree_s1(pf->filling, spaces('.', 1));
        pf->filling = ft_strjoinfree_s1(pf->filling, spaces('0', 6));
    }
    if (pf->need_format == 1)
        pf->filling = ft_strjoinfree_s1(pf->filling, spaces(' ', pf->width - len - pf->need_spase));
}

void    printf_float_2(long double tmp, int len, t_pf *pf)
{
    unsigned long long  left;
    char *src;
    long double         tmp1;

    tmp1 = tmp;
    tmp1 *= sign(pf, tmp, len);
    left = (unsigned long long)tmp1;
    tmp1 -= left;
    //printf("\n%Lf\n", tmp1);
    if (pf->flag == 1 && tmp1 > 0.5)
        left -= -1;
    if (tmp1 > 0.9999995 && pf->flag == 0 && pf->precision == 6)
        left -= -1;
    src = ft_strnew(ft_strlen(ft_itoa_long_long(left)));
    src = ft_itoa_long_long_uns(left);
    pf->filling = ft_strjoinfree_s2(pf->filling, src);
    printf_fill(pf, tmp1, len);
}

void    sign_2(t_pf *pf)
{
    if (pf->num < 0 && pf->zero_filling == 0)
    {
        pf->filling = ft_strjoinfree_s2("-", pf->filling);
        pf->flag = 1;
    }
    if (pf->need_sign == 1 && pf->num > 0 && pf->zero_filling == 0)
    {
        pf->filling = ft_strjoinfree_s2("+", pf->filling);
        pf->flag = 1;
    }
    if ((int)ft_strlen(pf->filling) != pf->width)
        if (pf->zero_filling == 1 && pf->align_left == 0 && pf->need_sign == 1)
        {
            pf->filling = ft_strjoinfree_s2(spaces('0', pf->width - (int)ft_strlen(pf->filling) - pf->need_spase - pf->need_sign * (pf->num > 0) - (pf->num < 0)), pf->filling);
        }
    if (pf->zero_filling == 1 && pf->align_left == 0 && pf->need_sign != 1)
    {
        pf->filling = ft_strjoinfree_s2(spaces('0', pf->width - (int)ft_strlen(pf->filling) - pf->need_spase * (pf->num > 0) - pf->zero_filling * (pf->num < 0)), pf->filling);
    }
}

void    printf_fill_3(t_pf *pf)
{
    if (pf->align_left == 1 && pf->need_sign == 1)
    {
        pf->filling = ft_strjoinfree_s1(pf->filling,
                                        spaces(' ', pf->width - (int) ft_strlen(pf->filling) - pf->need_sign * (pf->num > 0) * pf->zero_filling - (pf->num < 0) * !(pf->flag)));
    }
    else if (pf->align_left != 1 && pf->need_sign != pf->need_spase && pf->need_sign == 0)
    {
        pf->filling = ft_strjoinfree_s2(spaces(' ', pf->width - (int)ft_strlen(pf->filling) - pf->need_spase * !(pf->flag)), pf->filling);
    }
    else if (pf->align_left != 1 && pf->need_sign != pf->need_spase && pf->need_sign == 1 && pf->num > 0)
    {
        pf->filling = ft_strjoinfree_s2(spaces(' ', pf->width - (int) ft_strlen(pf->filling) - pf->need_spase - pf->need_sign * (pf->num > 0) * pf->zero_filling), pf->filling);
    }
    else if (pf->align_left != 1 && pf->need_sign != pf->need_spase && pf->need_sign == 1 && pf->num < 0 && pf->zero_filling == 0)
        pf->filling = ft_strjoinfree_s2(spaces(' ', pf->width - (int) ft_strlen(pf->filling) - pf->need_spase), pf->filling);
    else if (pf->align_left != 1 && pf->need_sign != pf->need_spase && pf->need_sign == 1 && pf->num < 0 && pf->zero_filling == 1)
        pf->filling = ft_strjoinfree_s2(spaces(' ', pf->width - (int) ft_strlen(pf->filling) - pf->need_spase - 1), pf->filling);
    else if (pf->align_left != 1 && pf->need_sign == pf->need_spase && pf->need_sign == 0 && pf->num > 0)
        pf->filling = ft_strjoinfree_s2(spaces(' ', pf->width - (int)ft_strlen(pf->filling)), pf->filling);
    else if (pf->align_left != 1 && pf->need_sign == pf->need_spase && pf->need_sign == 0 && pf->num < 0)
    {
        pf->filling = ft_strjoinfree_s2(spaces(' ', (pf->width - (int)ft_strlen(pf->filling) - (pf->zero_filling * ft_if_in_str(pf->filling, '-') | pf->zero_filling))), pf->filling);
    }
}

void    printf_fill_2(t_pf *pf)
{
    if (pf->align_left == 1 && pf->need_sign == 0)
    {
        pf->filling = ft_strjoinfree_s1(pf->filling,
                                        spaces(' ', pf->width - (int) ft_strlen(pf->filling) - (int)(pf->zero_filling * (pf->num < 0)) - pf->need_spase * (pf->num > 0)));
    }
    else
        printf_fill_3(pf);
    if ((pf->need_spase == 1) && (pf->num > 0) && (pf->need_sign == 0))
        pf->filling = ft_strjoinfree_s2(" ", pf->filling);
    if (pf->need_sign == 1 && pf->num > 0 && pf->zero_filling == 1)
        pf->filling = ft_strjoinfree_s2("+", pf->filling);
    if (pf->num < 0 && pf->zero_filling == 1)
        pf->filling = ft_strjoinfree_s2("-", pf->filling);
}

void    printf_float_3(long double tmp, t_pf *pf)
{
    unsigned long long  left;
    long double         tmp1;
    char *src;

    if ((tmp < 0))
        tmp1 = -tmp;
    else
        tmp1 = tmp;
    left = (unsigned long long)tmp1;
    tmp1 -= left;
    src = ft_strnew(ft_strlen(ft_itoa_long_long(left)));
    src = ft_itoa_long_long_uns(left);
    pf->filling = ft_strjoinfree_s2(pf->filling, src);
    if ((pf->flag == 1) && (pf->need_format == 1))
        pf->filling = ft_strjoinfree_s1(pf->filling, ".");
    pf->flag = 0;
    pf->filling = ft_strjoinfree_s2(pf->filling, ft_ftos_sec(ft_round(tmp1, ft_power(0.1, pf->precision)), pf->precision));
    sign_2(pf);
    printf_fill_2(pf);
}

void    print_float(t_pf *pf, long double num) {
    long double tmp;
    int len;

    pf->flag = 0;
    if (pf->precision == 0)
        pf->flag = 1;
    else if (pf->precision < 0)
        pf->precision = 6;
    tmp = num;
    len = ft_length(tmp, pf->precision);
    if (len > pf->width)
        printf_float_2(tmp, len, pf);
    else
        printf_float_3(tmp, pf);
    pf->printed += ft_strlen(pf->filling);
    ft_putstr(pf->filling);
}

int     handle_float(t_pf *pf)
{
    if (ft_strequ(pf->size_flag, "\0") == 1 || (pf->printed > 0 && pf->size_flag == NULL))
        pf->num = va_arg(pf->ap, double);
    else if (ft_strequ(pf->size_flag, "L") == 1)
        pf->num = (long double)va_arg(pf->ap, long double);
    if (pf->num == -5.0/0)
    {
        write(1, "-inf", 4);
        pf->printed += 4;
    }
    else if (pf->num == 5.0/0)
    {
        write(1, "inf", 3);
        pf->printed += 3;
    }
    else if (pf->num == -LDBL_MIN && pf->precision == 0)
    {
        write(1, "-0", 2);
        pf->printed += 2;
    }
    else
        print_float(pf, pf->num);
    return (pf->printed);
};