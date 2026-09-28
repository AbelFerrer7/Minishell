/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:57:59 by acerezo-          #+#    #+#             */
/*   Updated: 2024/10/02 12:27:01 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
		else
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

// 	t_list *new_back_element = ft_lstnew("sec");

// 	ft_lstadd_back(&head, new_back_element);

// 	assert(head == initial_element);
// 	assert(head->next == new_back_element);
// 	printf("Diferencia de elementos: %d\n", strcmp(head->content, "init"));

// 	free(initial_element);
// 	free(new_back_element);

// 	printf("Test: SUCCESS\n");
// 	return (0);
// }