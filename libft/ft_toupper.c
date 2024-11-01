/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-lda- <ana-lda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:29:43 by ana-lda-          #+#    #+#             */
/*   Updated: 2024/06/26 15:32:57 by ana-lda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c = c -32;
	return (c);
}
/*#include <stdio.h>
#include <ctype.h>

int main(void)
{
	printf("%i\n", ft_toupper('a'));
	printf("%i\n", toupper('a'));
}*/