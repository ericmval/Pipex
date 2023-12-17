/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltsmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin2 <emartin2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:23:54 by emartin2          #+#    #+#             */
/*   Updated: 2023/11/19 13:31:01 by emartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_elt;
	t_list	*temp;

	if (!lst)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		temp = f(lst->content);
		new_elt = ft_lstnew(temp);
		if (!new_elt)
		{
			del(temp);
			ft_lstclear (&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back (&new_lst, new_elt);
		lst = lst->next;
	}
	return (new_lst);
}
