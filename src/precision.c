/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:51:31 by jslave            #+#    #+#             */
/*   Updated: 2019/12/17 16:51:33 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				check_width(const char *curr, t_pf *pf)
{
	int quan;
	int width_of_num;

	if (ft_isdigit(*curr) == 1)
	{
		quan = ft_atoi(curr);
		if (quan >= 0)
		{
			pf->width = quan;
			width_of_num = find_len_of_num(quan);
			return (width_of_num);
		}
	}
	if (*curr == '*')
	{
		quan = (int)va_arg(pf->ap, int);
		if (quan < 0)
			quan *= (-1);
		pf->width = quan;
		return (1);
	}
	return (0);
}

int				prec_check_point(const char *curr, t_pf *pf, int *i)
{
	int j;

	j = 0;
	if (ft_isdigit(curr[j]) == 1 && curr[j] != '0' &&
find_types(&(curr[j]), TYPES) != 1 && find_types(&(curr[j]), "hl") != 1
	&& (pf->precision = ft_atoi(&curr[j])) > 0)
	{
		if (ft_strchr(&curr[j], '.') == 0)
			return (find_len_of_num(pf->precision) + j);
	}
	else if (curr[j] == '*')
		pf->precision = (int)va_arg(pf->ap, int);
	else if (curr[j] == '0')
		pf->precision = ft_atoi(&curr[j]);
	else if (find_types(&(curr[j]), TYPES) == 1)
	{
		pf->precision = -1;
		j++;
		*i += j;
		return (-1);
	}
	else
		pf->precision = -1;
	*i += j;
	return (0);
}

int				check_all_precisions(const char *curr, t_pf *pf)
{
	int i;
	int test;

	i = 0;
	while (*curr && curr[i] != '\0' && find_types(&(curr[i]), TYPES) != 1 &&
	find_types(&(curr[i]), "hl") != 1)
	{
		if (curr[i] == '.')
		{
			i++;
			test = prec_check_point(&curr[i], pf, &i);
			if (test == -1)
				break ;
			if (test)
				return (test);
		}
		i++;
	}
	return (i);
}

int				check_precision(const char *curr, t_pf *pf)
{
	int i;
	int width;

	i = check_all_precisions(curr, pf);
	if (pf->precision == -1)
		return (i - 1);
	if (pf->precision == 0)
		return (i);
	if (pf->precision > 0)
	{
		width = find_len_of_num(pf->precision);
		if (i > width + 1)
			return (i - width + 1);
		return (width + 1);
	}
	return (0);
}
