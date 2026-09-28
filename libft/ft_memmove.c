/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:26:11 by acerezo-          #+#    #+#             */
/*   Updated: 2024/09/18 12:31:35 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;

	ptr_dst = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	if (ptr_dst < ptr_src)
	{
		while (n--)
			*ptr_dst++ = *ptr_src++;
	}
	else
	{
		ptr_dst += n;
		ptr_src += n;
		while (n--)
			*--ptr_dst = *--ptr_src;
	}
	return (dest);
}
