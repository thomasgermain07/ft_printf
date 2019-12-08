/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 11:20:40 by thgermai          #+#    #+#             */
/*   Updated: 2019/12/08 13:52:13 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../libft/libft.h"

const char		*ft_refresh_str(const char *str)
{
	int				next_arg;

	next_arg = next_arg_index(str);
	if (str[next_arg] == '%')
	{
		next_arg++;
		while (str[next_arg] && define_type(str[next_arg]) == -1)
			next_arg++;
		next_arg++;
	}
	return (str + next_arg);
}

char			*redict_type(va_list args, char *output, t_param *param)
{
	char *(*fptr[9])(va_list, char *, t_param *);

	if (param->specifier < 0)
	{
		free(param);
		return (NULL);
	}
	fptr[0] = &pf_fill_char;
	fptr[1] = &pf_fill_str;
	fptr[2] = &pf_fill_add;
	fptr[3] = &pf_fill_deci;
	fptr[4] = &pf_fill_int;
	fptr[5] = &pf_fill_unsi;
	fptr[6] = &pf_fill_hexa;
	fptr[7] = &pf_fill_hexa_caps;
	fptr[8] = &pf_fill_modulo;
	return (output = (*fptr[param->specifier])(args, output, param));
}

int				ft_printf(const char *str, ...)
{
	va_list		args;
	char		*output;
	int			i;

	i = 0;
	if (!(output = ft_calloc(sizeof(char), 1)))
		return (-1);
	va_start(args, str);
	while (*str)
	{
		if (!(output = ft_strjoin_f12(output,
			ft_substr(str, 0, next_arg_index(str)))))
			return (ft_exit(-1, 1, output));
		if (str[next_arg_index(str)] == '%')
			if (!(output = redict_type(args, output,
				parcing_param(str + next_arg_index(str), args))))
				return (ft_exit(-1, 1, output));
		str = ft_refresh_str(str);
	}
	ft_putstr_fd(output, 1);
	va_end(args);
	return (ft_exit(ft_strlen(output), 1, output));
}
