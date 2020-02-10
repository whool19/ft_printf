/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 16:56:12 by jslave            #+#    #+#             */
/*   Updated: 2020/01/12 16:56:14 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				hex_i_less_one(t_pf *pf, int len)
{
	char *temp;

	temp = ft_strnew(len);
	ft_memset(temp, ' ', ft_strlen(temp));
	ft_memcpy(temp, "0x", 2);
	if (pf->filling[len - 2] == ' ')
	{
		ft_memcpy(&temp[2], pf->filling, len);
		ft_memcpy(pf->filling, temp, len);
	}
	else
	{
		ft_memcpy(&temp[2], pf->filling, len - 1);
		ft_memdel((void **)&pf->filling);
		pf->filling = ft_strdup(temp);
	}
	ft_memdel((void **)&temp);
}

void				transform_hex_format(t_pf *pf)
{
	int		i;
	int		len;
	char	*temp;

	i = 0;
	len = ft_strlen(pf->filling);
	while (pf->filling[i] == ' ')
		i++;
	if (pf->precision == -5 && pf->width && pf->zero_filling &&
	pf->filling[0] == '0' && pf->filling[1] == '0')
		pf->filling[1] = 'x';
	else if (i <= 1 && pf->filling[len - 1] != ' ')
	{
		temp = ft_strdup(&pf->filling[i]);
		ft_memdel((void **)&pf->filling);
		pf->filling = ft_strjoinfree_both(ft_strdup("0x"), temp);
	}
	else if (i <= 1 && pf->filling[len - 1] == ' ')
		hex_i_less_one(pf, len);
	else if (i >= 2)
		ft_memcpy(&pf->filling[i - 2], "0x", 2);
	else if ((pf->filling[0] == '0' && pf->filling[1] == '0') ||
	(pf->zero_filling == 0 && pf->width && pf->precision == -5))
		pf->filling[1] = 'x';
}

void				print_int_hex(t_pf *pf)
{
	unsigned long long int num;

	num = ft_atoi_long_long_uns(pf->filling);
	if (pf->precision >= 0 && pf->width > 0)
		handle_int_width_and_precision(pf, num);
	else if (pf->precision < 0)
	{
		if (pf->width != 0)
			handle_int_width(pf, num);
		else
			handle_int_precision(pf, num);
	}
	else if (pf->precision > 0 && pf->precision > (int)find_len_of_num(num))
		handle_int_precision(pf, num);
	if (pf->need_sign == 1 && num)
		handle_int_sign(pf, num);
	if (pf->need_spase == 1 && pf->need_sign != 1)
		handle_int_space(pf, num);
	if (pf->need_format == 1 && ft_atoi_base(pf->filling, 16) != 0)
		transform_hex_format(pf);
	if (pf->type == 'X')
		upper_symb(pf->filling);
	ft_putstr(pf->filling);
	pf->printed += ft_strlen(pf->filling);
}
