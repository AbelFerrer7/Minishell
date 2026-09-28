/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:23:07 by acerezo-          #+#    #+#             */
/*   Updated: 2024/10/07 13:34:59 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	sub_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		sub_len = s_len - start;
	else
		sub_len = len;
	substr = (char *)malloc(sizeof(char) * (sub_len + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, sub_len + 1);
	return (substr);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*str = "hola amigo!";
// 	char	*substr = ft_substr(str, 2, 8);
// 	printf("%s\n", substr);
// 	free(substr);
// 	return (0);
// }