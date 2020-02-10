/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 17:01:00 by jslave            #+#    #+#             */
/*   Updated: 2019/12/14 17:01:08 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/includes/libft.h"
# include <stdarg.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <float.h>

# define TYPES "cspdiouxXf%"
# define INT_TYPES "diouxXf"

typedef struct		s_pf
{
	va_list			ap;
	int				width;
	int				printed;
	int				align_left;
	int				need_sign;
	int				need_spase;
	int				need_format;
	int				zero_filling;
	int				precision;
	char			type;
	char			*size_flag;
	char			*filling;
	char			*str_empty;
	int				flag;
	long double		num;

}					t_pf;

/*
** char-str-percent.c
*/
int					handle_char(t_pf *pf);
int					handle_string(t_pf *pf);
int					handle_percent(t_pf *pf);
/*
**ft_printf.c
*/
int					ft_printf(const char *format, ...);
int					read_args(t_pf *pf, const char *format);
int					print_all(t_pf *pf);
/*
** ints.c
*/
int					handle_int(t_pf *pf);
void				handle_int_sign(t_pf *pf, long long int num);
void				push_string_one_sign(t_pf *pf);
void				print_int(t_pf *pf, long long int num);
/*
** ints_utils_1.c
*/
int					handle_max_and_min_long_long(t_pf *pf);
char				*fill_zero_string(t_pf *pf, int len, long long int num);
void				fill_empty_str_neg_num(t_pf *pf, int len, long long num);
void				fill_empty_str_pos_num(t_pf *pf, int len);
/*
**  int_utils_2.c
*/
void				handle_int_width_and_precision(t_pf *pf, long long int num);
void				handle_int_space(t_pf *pf, long long int num);
void				ft_str_overlap_copy(char *str);
void				handle_int_width(t_pf *pf, long long int num);
/*
** int_utils_3.c
*/
void				handle_int_precision(t_pf *pf, long long int num);
void				turn_width_more_prec(t_pf *pf, long long int num, int len);
void				prec_less_width(t_pf *pf, long long int num, int len);
void				put_sign(t_pf *pf, long long int num);
/*
** parsing.c
*/
int					find_types(const char *str, char *parent);
int					check_types(const char *curr, t_pf *pf);
int					zero_or_space_string(t_pf *pf);
int					check_size_flag(const char *curr, t_pf *pf);
void				put_size_flag(const char *curr, t_pf *pf);
/*
** pnt_uns_hex.c
*/
void				handle_pnt_no_prec(t_pf *pf);
int					handle_pointer(t_pf *pf);
int					handle_hex(t_pf *pf);
int					handle_unsigned(t_pf *pf);
/*
** precision.c
*/
int					check_width(const char *curr, t_pf *pf);
int					prec_check_point(const char *curr, t_pf *pf, int *i);
int					check_precision(const char *curr, t_pf *pf);
int					check_all_precisions(const char *curr, t_pf *pf);
/*
** str.c
*/
void				fill_and_print_string(t_pf *pf);
void				print_char(t_pf *pf);
void				transform_str_precision(t_pf *pf);
char				*cut_string(char *str, int q);
/*
** utils.c
*/
t_pf				*init_pf(void);
void				upper_symb(char *str);
void				zero_pf(t_pf *pf);
/*
** oct_test.c
*/
int					handle_oct(t_pf *pf);
void				print_int_oct(t_pf *pf);
void				check_zero(t_pf *pf);
/*
** hex.c
*/
void				hex_i_less_one(t_pf *pf, int len);
void				transform_hex_format(t_pf *pf);
void				print_int_hex(t_pf *pf);
/*
** floats.c
*/
int					dbl(t_pf *pf);
int					handle_float(t_pf *pf);
int					sign(t_pf *pf, long double tmp, int len);
int					ft_length(long double num, int prec);
/*
** floats_2.c
*/
int					ft_if_in_str(char *s1, char s2);
double				ft_power(double nb, double power);
char				*spaces(char c, int n);
long double			ft_round(long double x, long double acc);
char				*ft_ftos_sec(long double num, int prec);
/*
** floats_3.c
*/
void				printf_fill(t_pf *pf, long double tmp, int len);
void				printf_float_2(long double tmp, int len, t_pf *pf);
void				sign_2(t_pf *pf);
void				printf_fill_4(t_pf *pf);
/*
** floats_4.c
*/
void				printf_fill_3(t_pf *pf);
void				printf_fill_2(t_pf *pf);
void				printf_float_3(long double tmp, t_pf *pf);
void				print_float(t_pf *pf, long double num);

void			print_int_uns(t_pf *pf, unsigned long long int num);
void			handle_int_space_uns(t_pf *pf, unsigned long long int num);
void			handle_int_width_and_precision_uns(t_pf *pf, unsigned long long
int num);
void			handle_int_width_uns(t_pf *pf);
void			handle_int_precision_uns(t_pf *pf, unsigned long long int num);
void		    handle_int_space_2_uns(t_pf *pf, unsigned long long int num,
		int len);
void			turn_width_more_prec_uns(t_pf *pf, int len);
#endif
