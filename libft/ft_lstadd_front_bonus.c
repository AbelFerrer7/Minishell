/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:36:34 by acerezo-          #+#    #+#             */
/*   Updated: 2024/09/26 13:33:15 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}

// #include "libft.h"
// #include <assert.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
// 	t_list *initial_element = ft_lstnew("init");
// 	t_list *head = initial_element;

// 	t_list *new_front_element = ft_lstnew("sec");

// 	ft_lstadd_front(&head, new_front_element);

// 	assert(head == new_front_element);
// 	assert(head->next == initial_element);
// 	printf("%d\n", strcmp(head->content, "sec"));

// 	free(initial_element);
// 	free(new_front_element);

// 	printf("Test: SUCCESS\n");
// 	return (0);
// }