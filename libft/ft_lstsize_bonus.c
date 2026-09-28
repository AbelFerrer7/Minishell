/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:39:47 by acerezo-          #+#    #+#             */
/*   Updated: 2024/09/26 13:10:20 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	len;

	len = 0;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

// #include <stdio.h>
// int	main(void)
// {
// 	t_list *list;
// 	list = ft_lstnew("Hoe");
// 	t_list *cpy;
// 	cpy = ft_lstnew("Hoe");
// 	list->next = cpy;
// 	printf("%d", ft_lstsize(list));
// }