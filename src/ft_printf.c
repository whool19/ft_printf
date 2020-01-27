/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 17:02:07 by jslave            #+#    #+#             */
/*   Updated: 2019/12/14 17:02:17 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		                print_all(t_pf *pf)
{
	if (pf->width != 0)
		if (zero_or_space_string(pf) == -1)
			return (-1);
	if (pf->type == 'c')
        return (handle_char(pf));
	else if (pf->type == 's')
        return (handle_string(pf));
	else if (pf->type == 'p')
		return (handle_pointer(pf));
	else if (pf->type == 'd' || pf->type == 'i')
		return (handle_int(pf));
	else if (pf->type == 'o')
        return (handle_oct(pf));
	else if (pf->type == 'u')
	    return (handle_unsigned(pf));
	else if (pf->type == 'x' || pf->type == 'X')
		return (handle_hex(pf));
	else if (pf->type == 'f')
		return (handle_float(pf));
	else if (pf->type == '%')
		return (handle_percent(pf));
    return (-1);
}

int 		read_args(t_pf *pf, const char *format)
{
	int i;
	i = 0;
	int len = ft_strlen(format);

	while (format[i] != '\0' && i < len)
	{
		if (format[i] != '%' && format[i] != '\0')
		{
			ft_putchar(format[i]);
			pf->printed++;
		}
		else if (format[i] == '%')
		{
			i++;
			i+=check_flags(&format[i], pf);
			i+=check_width(&format[i], pf);
			i+=check_precision(&format[i], pf);
			i+=check_size_flag(&format[i], pf);
			i+=check_types(&format[i], pf);
			if (print_all(pf) >= 0)
			    zero_pf(pf);
		}
		i++;
	}
	return (i);
}

int         ft_printf(const char *format, ...)
{
	t_pf *pf;
	int i;

	if (format == NULL || (pf = init_pf()) == NULL)
		return (0);
	va_start(pf->ap, format);
	if (read_args(pf, format) < 0)
    {
	    //free_pf(pf);
	    zero_pf(pf);
        return (-1);
    }
	va_end(pf->ap);
	i = pf->printed;
    free(pf);
	return (i);
}




