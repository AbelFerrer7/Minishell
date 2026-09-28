/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:17:42 by acerezo-          #+#    #+#             */
/*   Updated: 2024/09/23 13:18:24 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_getlen(int nb)
{
	size_t			i;
	unsigned int	nbr;

	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nbr = (unsigned int)-nb;
		i++;
	}
	else
		nbr = (unsigned int)nb;
	while (nbr > 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	size_t			len;
	unsigned int	temp;

	len = ft_getlen(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		temp = (unsigned int)-n;
		str[0] = '-';
	}
	else
		temp = (unsigned int)n;
	if (n == 0)
		str[0] = '0';
	while (len-- && temp > 0)
	{
		str[len] = (temp % 10) + '0';
		temp /= 10;
	}
	return (str);
}

// #include <stdio.h>
// int main()
// {
//     printf("%s\n", ft_itoa(-1)); // Should correctly print "-1"
// }