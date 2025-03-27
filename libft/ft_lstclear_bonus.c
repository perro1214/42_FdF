/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:01:34 by hhayato           #+#    #+#             */
/*   Updated: 2024/11/12 13:45:45 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*to_org;
	t_list	*to_nex;

	if ((lst == NULL) || (del == NULL))
	{
		return ;
	}
	to_org = *lst;
	while (to_org != NULL)
	{
		to_nex = to_org->next;
		(*del)(to_org->content);
		free(to_org);
		to_org = to_nex;
	}
	*lst = NULL;
}
