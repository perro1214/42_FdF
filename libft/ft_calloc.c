/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:49:32 by hhayato           #+#    #+#             */
/*   Updated: 2024/11/09 12:27:46 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*result;

	if (n == 0 || size == 0)
	{
		result = malloc(0);
		return (result);
	}
	if (((SIZE_MAX / n) < size))
	{
		return (NULL);
	}
	result = malloc(n * size);
	if (!result)
		return (NULL);
	ft_bzero(result, n * size);
	return (result);
}

// int main(void)
// {
//    int *ptr,*p;
//    int i;

//    /* 500個のintサイズのメモリを確保 */
//    ptr = (int *)ft_calloc(500,sizeof(int));
//    if(ptr == NULL) {
//       printf("メモリが確保できません\n");
//       exit(EXIT_FAILURE);
//    }

//    p = ptr;
//    for (i=0; i<500; i++) {
//       *p = i;
//       printf("%d ",*p);
//       p++;
//    }

//    /* メモリの開放 */
//    free(ptr);

//    return (0);
// }

// int	main(void)
// {
// 	char *result = calloc(0, 0);
// 	if (result != NULL)
// 	{
// 		printf("%s", "yes");
// 	}
// }