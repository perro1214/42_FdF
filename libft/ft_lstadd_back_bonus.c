/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhayato <hhayato@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:01:08 by hhayato           #+#    #+#             */
/*   Updated: 2024/11/12 13:45:04 by hhayato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*end;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	end = *lst;
	while (end->next != NULL)
	{
		end = end->next;
	}
	end->next = new;
}
