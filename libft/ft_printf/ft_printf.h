/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:35:33 by ykot              #+#    #+#             */
/*   Updated: 2022/09/09 12:34:11 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../libft.h"
# include <stdarg.h>
# define MAX_WP 21474836

typedef struct s_flags
{
	char	specifier;
	int		hash;
	int		zero;
	int		minus;
	int		plus;
	int		space;
	int		width;
	int		precision;
	int		modifier;
	int		negative;
	int		arg_zero;
	int		zero_printed;
	int		int_round;
	int		total;
}				t_flags;

typedef void	t_conversion(t_flags *flag, va_list *ap);

int			ft_printf(const char *str, ...);
int			conv_spec(const char *str, int *i, t_flags *flag, va_list *ap);
void		check_unarg(unsigned long long arg, t_flags *flag);
void		check_minus_arg(long long arg, t_flags *flag);
void		check_minus_arg_f(long double *arg, t_flags *flag);
void		check_hash_width(t_flags *flag);
void		read_flags(const char *str, int *i, t_flags *flag);
void		read_precision_width(const char *str, int *i, \
				t_flags *flag, int is_prec);
void		read_modifier(const char *str, int *i, t_flags *flag);
void		read_star(int *i, t_flags *flag, va_list *ap, int is_prec);
void		print_sign(t_flags *flag);
void		print_flag_space(t_flags *flag);
void		print_hash(t_flags *flag);
void		print_sign_or_hash(t_flags *flag, int num_dig);
void		print_precision(t_flags *flag, int num_dig);
void		print_width(t_flags *flag, int num_dig, int first_call);
void		putspace(t_flags *flag);
void		putllunbr(unsigned long long n);
long long	smaller(long long a, long long b);
void		print_percent(t_flags *flag);
void		print_char(t_flags *flag, va_list *ap);
void		print_pointer(t_flags *flag, va_list *ap);
void		print_str(t_flags *flag, va_list *ap);
void		print_decimal(t_flags *flag, va_list *ap);
void		print_unsigned(t_flags *flag, va_list *ap);
void		print_octal(t_flags *flag, va_list *ap);
void		print_hexadecimal(t_flags *flag, va_list *ap);
void		print_binary(t_flags *flag, va_list	*ap);
int			print_conv(t_flags *flag, va_list *ap);
void		print_float(t_flags *flag, va_list *ap);
int			count_dig(char	*part_int, t_flags *flag);
void		read_arg_f(long double *arg, t_flags *flag, va_list *ap);
char		*read_int_part(long double *arg);
char		*read_frac_part(long double arg, t_flags *flag);
void		print_width_f(t_flags *flag, int num_dig, int first_call);
void		print_sign_f(t_flags *flag, int num_dig);
int			bank_round(long double arg, char *part_int, t_flags *flag);
int			round_int(char **str, int is_int_part, t_flags *flag, int m);
int			rounding(char **str, int is_int_part, t_flags *flag);

#endif