/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:30:31 by acerezo-          #+#    #+#             */
/*   Updated: 2024/09/23 11:58:34 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		s2len;
	char	*str;

	i = ft_strlen(s1);
	j = 0;
	s2len = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s2len + i + 1));
	if (!str)
		return (NULL);
	while (j < i)
	{
		str[j] = s1[j];
		j++;
	}
	i = 0;
	while (i < s2len)
	{
		str[j] = s2[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}

// #include <stdio.h>
// int	main(void)
// {
// 	printf("%s", ft_strjoin("Hello ", "World!!!"));
// }