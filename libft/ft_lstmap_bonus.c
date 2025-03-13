/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:03:04 by hhayato           #+#    #+#             */
/*   Updated: 2024/11/12 13:46:21 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*to_org;
	t_list	*to_nex;

	to_org = NULL;
	while (lst != NULL)
	{
		to_nex = ft_lstnew((*f)(lst->content));
		if (to_nex == NULL)
		{
			ft_lstclear(&to_org, del);
			return (NULL);
		}
		ft_lstadd_back(&to_org, to_nex);
		lst = lst->next;
	}
	return (to_org);
}
