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

int			find_step(long long int num)
{
	int res;

	res = 0;
	if (num < 0)
    {
        res++;
        num*=-1;
    }

	while (num)
	{
		res++;
		num = num / 10;
	}
	return (res);
}

int			check_width(const char *curr, t_pf *pf)
{
	int quan;
	int width_of_num;

	if (ft_isdigit(*curr) == 1)
	{
		quan = ft_atoi(curr);
		if (quan >= 0)
		{
			pf->width = quan;
			width_of_num = find_step(quan);
			return (width_of_num);
		}
	}
	if (*curr == '*')
	{
		quan = (int)va_arg(pf->ap, int);
		pf->width = quan;
		return (1);
	}
	return (0);
}

int			check_all_precisions(const char *curr, t_pf *pf)
{
	int i;

	i = 0;
	while (*curr && curr[i] != '\0' && find_types(&(curr[i]), TYPES) != 1)
	{
		if (curr[i] == '.')
		{
			if (ft_isdigit(curr[++i]) == 1 && curr[i] != '0' && find_types(&(curr[i]), TYPES) != 1 && (ft_atoi(&curr[i])) > 0)
            {
                pf->precision = ft_atoi(&curr[i]);
                if (ft_strchr(&curr[i], '.') == 0)
                    return (find_step(pf->precision) + i);
            }
			else if (curr[i] == '*')
				pf->precision = (int)va_arg(pf->ap, int);
			else if (curr[i] == '0')
				pf->precision = ft_atoi(&curr[i]);
			else if (find_types(&(curr[i]), TYPES) == 1)
			{
				pf->precision = -1;
				i+=1;
				break;
			}
			else
				pf->precision = -1;
		}
		i++;
	}
	return (i);
}

int 	check_precision(const char *curr, t_pf *pf)
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
		width = find_step(pf->precision);
        if (i > width + 1)///////////////////////////////////////////////////////////
		    return (i - width + 1);
        return (width + 1);
	}
	return (0);
}