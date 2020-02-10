/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:40:00 by jslave            #+#    #+#             */
/*   Updated: 2020/02/07 16:40:05 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		handle_int_space_2(t_pf *pf, long long int num, int len)
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

void			handle_int_width(t_pf *pf, long long int num)
{
	int len;

	len = ft_strlen(pf->filling);
	if (pf->width > len)
	{
		if (num < 0)
			fill_empty_str_neg_num(pf, len, num);
		else
			fill_empty_str_pos_num(pf, len);
		ft_memdel((void **)&pf->filling);
		pf->filling = ft_strdup(pf->str_empty);
	}
}

void			handle_int_space(t_pf *pf, long long int num)
{
	int len;

	if (handle_max_and_min_long_long(pf) == 1)
		return ;
	len = find_len_of_num((int)num);
	if (pf->precision <= 0 && pf->width == 0 && num >= 0)
		pf->filling = ft_strjoinfree_both(ft_strdup(" "), pf->filling);
	else if (pf->precision <= 0 && pf->width > 0 && num >= 0)////
		handle_int_space_2(pf, num, len);
	else if (pf->width > pf->precision && num >= 0)
	{
		if (pf->align_left != 1)
		{
			if (pf->filling[0] == '0')
				pf->filling[0] = ' ';
		}
		else
			ft_str_overlap_copy(pf->filling);
	}
	else if (num >= 0)
		pf->filling = ft_strjoinfree_both(ft_strdup(" "), pf->filling);
}

void			handle_int_width_and_precision(t_pf *pf, long long int num)
{
	int len;

	handle_int_precision(pf, num);
	len = ft_strlen(pf->filling);
	if (pf->width > pf->precision)
	{
		if (pf->precision != 0 && pf->precision != -1)
			turn_width_more_prec(pf, num, len);
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
		handle_int_precision(pf, num);
}

void			ft_str_overlap_copy(char *str)
{
	char	*tmp;
	size_t	len;
	int		i;
	int		j;

	i = 1;
	j = 0;
	len = ft_strlen(str);
	tmp = ft_strnew(len);
	ft_memcpy(tmp, str, len);
	while (len - 1)
	{
		str[i] = tmp[j];
		i++;
		j++;
		len--;
	}
	str[0] = ' ';
	free(tmp);
}
