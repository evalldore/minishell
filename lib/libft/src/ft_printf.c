/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:18:29 by evallee-          #+#    #+#             */
/*   Updated: 2023/05/11 16:33:18 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_writearg(va_list *args, char c)
{
	if (!c)
		return (0);
	if (c == 'c')
		return (ft_putchar_fd(va_arg(*args, int), 1));
	if (c == 's')
		return (ft_putstr_fd(va_arg(*args, char *), 1));
	if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(*args, int), 1));
	if (c == 'u')
		return (ft_putuint_fd(va_arg(*args, unsigned int), 1));
	if (c == '%')
		return (ft_putchar_fd('%', 1));
	if (c == 'x')
		return (ft_puthex_fd((uint32_t)va_arg(*args, int), false, 1));
	if (c == 'X')
		return (ft_puthex_fd((uint32_t)va_arg(*args, int), true, 1));
	if (c == 'p')
		return (ft_putaddr_fd(va_arg(*args, void *), 1));
	return (0);
}

int	ft_printf(const char *f, ...)
{
	va_list			args;
	int				len;
	char			ct;

	len = 0;
	va_start(args, f);
	while (*f)
	{
		ct = *f++;
		if (ct != '%')
			len += write(1, &ct, 1);
		else
			len += ft_writearg(&args, *f++);
	}
	va_end(args);
	return (len);
}
