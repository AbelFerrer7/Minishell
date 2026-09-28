/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:24:31 by acerezo-          #+#    #+#             */
/*   Updated: 2024/10/02 13:13:21 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!f)
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	t_list *list;
// 	t_list *list2;

// 	list = ft_lstnew("Holb");
// 	list2 = ft_lstnew("Hola");
// 	ft_lstadd_back(&list, list2);
// 	void *temp = list->content;
// 	list = list->next;
// 	printf("%d", strcmp(list->content, temp));
// }