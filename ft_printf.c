/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmartin- <gmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:59:34 by gmartin-          #+#    #+#             */
/*   Updated: 2020/01/22 18:19:27 by gmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

int ft_putchar(char c, int n)
{
	int len = 0;
    while (n-- > 0)
	{
		write(1, &c, 1);
    	len++;
	}
	return (len);
}

int ft_putstr(char *str, int n)
{
	int len = 0;
	while (n-- > 0)
    {
        write(1, &str[len], 1);
    	len++;
    }
	return (len);
}

int    ft_str(char *str, int space, int zero, int len)
{
    int size = 0;
    if (str == NULL)
        str = "(null)";
    while (str[size])
        size++;
    if (zero >= 0 && zero < size)
        size = zero;
    if (space > size)
        len += ft_putchar(' ', space - size);
    len += ft_putstr(str, size);
    return (len);
}

char            *ft_itoa(long int n)
{
    int     aux;
    int     len;
    char    *str;
    
    aux = n;
    len = 1;

    while (aux /= 10)
        len++;
    if ((str = (char*)malloc(sizeof(char) * len + 1)) == NULL)
        return (NULL);
    str[len] = '\0';
    while (len--)
    {
        str[len] = n % 10 + '0';
        n = n / 10;
    }
    return (str);
}

int	ft_int(long int d, int space, int zero, int len)
{
    int size = 0;
    int negative = 0;
    if (d < 0)
    {
        d *= -1;
        negative = -1;
        space += -1;
    }
    char *str = ft_itoa(d);
    while (str[size])
        size++;
	if (zero == 0 && d == 0)
		size = 0;
    if (space > size)
    {
        if (zero <= size)
            space = space - size;
        else if (zero > size)
            space = space - zero;
	}
    else
        space = 0;
    len += ft_putchar(' ', space);
    if (negative == -1)
    	len += ft_putchar('-', 1);
    len += ft_putchar('0', zero - size);
	len += ft_putstr(str, size);
    return (len);
}

char            *ft_unsigneditoa(unsigned int n)
{
    unsigned int        aux;
    int                   len;
    char                *str;
    
    aux = n;
    len = 1;
    while (aux /= 16)
        len++;
    if ((str = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
        return (NULL);
    str[len] = '\0';
    while (len--)
    {
        if ((n % 16) < 10)
            str[len] = n % 16 + '0';
        if ((n % 16) > 9)
            str[len] = n % 16 + 'W';
        n = n / 16;
    }
    return (str);
}


int    ft_hex(unsigned int d, int space, int zero, int len)
{
    int size = 0;
    
    char *str = ft_unsigneditoa(d);
    while (str[size])
        size++;
    if (zero == 0 && d == 0)
        size = 0;
    if (space > size)
    {
        if (zero <= size)
            space = space - size;
        else if (zero > size)
            space = space - zero;
	}
    else
        space = 0;
    len += ft_putchar(' ', space);
    len += ft_putchar('0', zero - size);
	len += ft_putstr(str, size);
    return (len);
}
int ft_printf(const char *format, ...)
{
	int len = 0;
	int space = 0;
	int zero = -1;
	va_list ap;

	va_start(ap, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			space = 0;
			zero = -1;
			format++;
			while (*format >= '0' && *format <= '9')
			{
				space = space * 10 + (*format - '0');
				format++;
			}
			if (*format == '.')
			{
				format++;
                zero = 0;
				while (*format >= '0' && *format <= '9')
				{
					zero = zero * 10 + (*format - '0');
					format++;
				}
			}	
			if (*format == 's')
			{
				len = ft_str(va_arg(ap, char*), space, zero, len);
				format++;
			}
			else if (*format == 'd')
			{
				len = ft_int((long int)(va_arg(ap, int)), space, zero, len);
				format++;
			}
			else if (*format == 'x')
			{
				len = ft_hex(va_arg(ap, unsigned int), space, zero, len);
				format++;
			}
		}		
		else
		{
			write(1, format, 1);
			format++;
			len++;
		}
	}
	va_end(ap);
	return (len);
}
/*
int main ()
{
	int x = 0;
	int y = 0;

	char *s = "GONZALO";
    int d = -2147483648;
    //int hex = 1500;
	x = printf("hola|%10.10d|%15.14d|%4.30d|%0.d|%.d|\n", d, d, d, d, 0);
	printf("%d\n", x);

	y = ft_printf("hola|%10.10d|%15.14d|%4.30d|%0.d|%.d|\n", d, d, d, d, 0);
	ft_printf("%d\n", y);
    
    x = printf("hola|%10.10x|%15.14x|%8.15x|%0.x|%.x|\n", d, d, d, d, 0);
    printf("%d\n", x);
    
    y = ft_printf("hola|%10.10x|%15.14x|%8.15x|%0.x|%.x|\n", d, d, d, d, 0);
    ft_printf("%d\n", y);
    
    x = printf("hola|%10s|%15.14s|%8.10s|%.s|%.4s\n", s, s, s, s, NULL);
    printf("%d\n", x);
    
    y = ft_printf("hola|%10s|%15.14s|%8.10s|%.s|%.4s\n", s, s, s, s, NULL);
    ft_printf("%d\n", y);
}

int main (void)
{
    int    r;
    r = 0;
    r += ft_printf("Simple test\n");
    r += ft_printf("");
    r += ft_printf("--Format---");
    r += ft_printf("\n");
    r += ft_printf("%d", 0);
    r += ft_printf("%d", 42);
    r += ft_printf("%d", 1);
    r += ft_printf("%d", 5454);
    r += ft_printf("%d", (int)2147483647);
    r += ft_printf("%d", (int)2147483648);
    r += ft_printf("%d", (int)-2147483648);
    r += ft_printf("%d", (int)-2147483649);
    r += ft_printf("\n");
    r += ft_printf("%x", 0);
    r += ft_printf("%x", 42);
    r += ft_printf("%x", 1);
    r += ft_printf("%x", 5454);
    r += ft_printf("%x", (int)2147483647);
    r += ft_printf("%x", (int)2147483648);
    r += ft_printf("%x", (int)-2147483648);
    r += ft_printf("%x", (int)-2147483649);
    r += ft_printf("%s", "");
    r += ft_printf("%s", "toto");
    r += ft_printf("%s", "wiurwuyrhwrywuier");
    r += ft_printf("%s", NULL);
    r += ft_printf("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
    r += ft_printf("\n--Mixed---\n");
    r += ft_printf("%d%x%d%x%d%x%d%x\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
    r += ft_printf("-%d-%x-%d-%x-%d-%x-%d-%x-\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
    r += ft_printf("\n");
    r += ft_printf("%s%s%s%s\n", "", "toto", "wiurwuyrhwrywuier", NULL);
    r += ft_printf("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
    r += ft_printf("--1 r += printflag--\n");
    r += ft_printf("d0w %0d %0d %0d %0d %0d %0d %0d %0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("d4w %4d %4d %4d %4d %4d %4d %4d %4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("d10w %10d %10d %10d %10d %10d %10d %10d %10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("d0p %.0d %.0d %.0d %.0d %.0d %.0d %.0d %.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("d4p %.4d %.4d %.4d %.4d %.4d %.4d %.4d %.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("d10p %.10d %.10d %.10d %.10d %.10d %.10d %.10d %.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("x0w %0x %0x %0x %0x %0x %0x %0x %0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("x4w %4x %4x %4x %4x %4x %4x %4x %4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("x10w %10x %10x %10x %10x %10x %10x %10x %10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("x0p %.0x %.0x %.0x %.0x %.0x %.0x %.0x %.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("x4p %.4x %.4x %.4x %.4x %.4x %.4x %.4x %.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("x10p %.10x %.10x %.10x %.10x %.10x %.10x %.10x %.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("s0p ~%.0s` ~%.0s` ~%.0s` ~%.0s` ~%.0s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    r += ft_printf("s4w ~%4s` ~%4s` ~%4s` ~%4s` ~%4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    r += ft_printf("s4p ~%.4s` ~%.4s` ~%.4s` ~%.4s` ~%.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    r += ft_printf("s10w ~%10s` ~%10s` ~%10s` ~%10s` ~%10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    r += ft_printf("s10p ~%.10s` ~%.10s` ~%.10s` ~%.10s` ~%.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    r += ft_printf("--2 r += printflags--\n");
    r += ft_printf("d0w0p %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("x0w0p %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("--Precision--\n");
    r += ft_printf("d0w4p %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("d0w10p %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("x0w4p %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("x0w10p %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("--Width--\n");
    r += ft_printf("d4w0p %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("d10w0p %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("x4w0p %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("x10w0p %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("s4w0p ~%4.s` ~%4.s` ~%4.s` ~%4.s` ~%4.s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    r += ft_printf("s10w0p ~%10.0s` ~%10.0s` ~%10.0s` ~%10.0s` ~%10.0s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    r += ft_printf("--Width and Precision--\n");
    r += ft_printf("d10w4p %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("d10w10p %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("d4w4p %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("d4w10p %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("x10w4p %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("x10w10p %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("x4w4p %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("x4w10p %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += ft_printf("s10w4p ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    r += ft_printf("s10w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    r += ft_printf("s4w4p ~%4.4s` ~%4.4s` ~%4.4s` ~%4.4s` ~%4.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    r += printf("s4w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);

	printf("written: %d\n", r);
}
*/
int main (void)
{
    int    r;
    r = 0;
    r += printf("Simple test\n");
    r += printf("");
    r += printf("--Format---");
    r += printf("\n");
    r += printf("%d", 0);
    r += printf("%d", 42);
    r += printf("%d", 1);
    r += printf("%d", 5454);
    r += printf("%d", (int)2147483647);
    r += printf("%d", (int)2147483648);
    r += printf("%d", (int)-2147483648);
    r += printf("%d", (int)-2147483649);
    r += printf("\n");
    r += printf("%x", 0);
    r += printf("%x", 42);
    r += printf("%x", 1);
    r += printf("%x", 5454);
    r += printf("%x", (int)2147483647);
    r += printf("%x", (int)2147483648);
    r += printf("%x", (int)-2147483648);
    r += printf("%x", (int)-2147483649);
    r += printf("%s", "");
    r += printf("%s", "toto");
    r += printf("%s", "wiurwuyrhwrywuier");
    r += printf("%s", NULL);
    r += printf("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
    r += printf("\n--Mixed---\n");
    r += printf("%d%x%d%x%d%x%d%x\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
    r += printf("-%d-%x-%d-%x-%d-%x-%d-%x-\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
    r += printf("\n");
    r += printf("%s%s%s%s\n", "", "toto", "wiurwuyrhwrywuier", NULL);
    r += printf("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
    r += printf("--1 r += printflag--\n");
    r += printf("d0w %0d %0d %0d %0d %0d %0d %0d %0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("d4w %4d %4d %4d %4d %4d %4d %4d %4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("d10w %10d %10d %10d %10d %10d %10d %10d %10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("d0p %.0d %.0d %.0d %.0d %.0d %.0d %.0d %.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("d4p %.4d %.4d %.4d %.4d %.4d %.4d %.4d %.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("d10p %.10d %.10d %.10d %.10d %.10d %.10d %.10d %.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("x0w %0x %0x %0x %0x %0x %0x %0x %0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("x4w %4x %4x %4x %4x %4x %4x %4x %4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("x10w %10x %10x %10x %10x %10x %10x %10x %10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("x0p %.0x %.0x %.0x %.0x %.0x %.0x %.0x %.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("x4p %.4x %.4x %.4x %.4x %.4x %.4x %.4x %.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("x10p %.10x %.10x %.10x %.10x %.10x %.10x %.10x %.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("s0p ~%.0s` ~%.0s` ~%.0s` ~%.0s` ~%.0s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    r += printf("s4w ~%4s` ~%4s` ~%4s` ~%4s` ~%4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    r += printf("s4p ~%.4s` ~%.4s` ~%.4s` ~%.4s` ~%.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    r += printf("s10w ~%10s` ~%10s` ~%10s` ~%10s` ~%10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    r += printf("s10p ~%.10s` ~%.10s` ~%.10s` ~%.10s` ~%.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    r += printf("--2 r += printflags--\n");
    r += printf("d0w0p %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("x0w0p %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("--Precision--\n");
    r += printf("d0w4p %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("d0w10p %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("x0w4p %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("x0w10p %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("--Width--\n");
    r += printf("d4w0p %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("d10w0p %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("x4w0p %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("x10w0p %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("s4w0p ~%4.s` ~%4.s` ~%4.s` ~%4.s` ~%4.s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    r += printf("s10w0p ~%10.0s` ~%10.0s` ~%10.0s` ~%10.0s` ~%10.0s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    r += printf("--Width and Precision--\n");
    r += printf("d10w4p %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("d10w10p %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("d4w4p %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("d4w10p %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("x10w4p %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("x10w10p %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("x4w4p %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("x4w10p %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
    r += printf("s10w4p ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    r += printf("s10w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    r += printf("s4w4p ~%4.4s` ~%4.4s` ~%4.4s` ~%4.4s` ~%4.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
    r += printf("s4w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);

	printf("written: %d\n", r);
}
/**/
