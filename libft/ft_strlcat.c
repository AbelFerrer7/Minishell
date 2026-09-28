/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:30:43 by acerezo-          #+#    #+#             */
/*   Updated: 2024/09/18 15:11:13 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	destlen;

	destlen = 0;
	while (dest[destlen] != '\0' && destlen < size)
		destlen++;
	i = destlen;
	while (src[destlen - i] && destlen + 1 < size)
	{
		dest[destlen] = src[destlen - i];
		destlen++;
	}
	if (i < size)
		dest[destlen] = '\0';
	return (i + ft_strlen(src));
}
