/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:42:24 by acerezo-          #+#    #+#             */
/*   Updated: 2024/10/07 18:30:53 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getchar(char const *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i])
		if (s1[i++] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*new;
	size_t	len;
	size_t	k;

	i = 0;
	k = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	while (ft_getchar(set, s1[i]) && s1[i])
		i++;
	while (ft_getchar(set, s1[len - 1]) && (len - 1))
		len--;
	if (len < i)
		len = i;
	new = malloc(len - i + 1);
	if (!new)
		return (NULL);
	while (i < len)
		new[k++] = s1[i++];
	new[k] = '\0';
	return (new);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%s", ft_strtrim("HolaAmigoPaco", "abcdefghijklmnopqrstuvwzyz"));
// }