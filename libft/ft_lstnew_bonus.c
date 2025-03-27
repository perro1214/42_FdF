/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:03:13 by hhayato           #+#    #+#             */
/*   Updated: 2024/11/12 13:46:25 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*result;

	result = malloc(sizeof(t_list));
	if (result == NULL)
	{
		return (NULL);
	}
	result->content = content;
	result->next = NULL;
	return (result);
}

// int main(void){
//     t_list *ans;
//     char *i = "abcde";
//     ans = ft_lstnew(i);
//     printf("%s",(char *)ans->content);
// }
