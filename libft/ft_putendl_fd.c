/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acerezo- <acerezo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:45:39 by acerezo-          #+#    #+#             */
/*   Updated: 2024/09/23 13:48:46 by acerezo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int		i;
	char	endln;

	i = 0;
	endln = '\n';
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, &endln, 1);
}

// #include <fcntl.h>
// int main()
// {
// 	int fd = open("test", O_RDWR | O_CREAT);
// 	ft_putendl_fd("keloke", fd);
// }