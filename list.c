/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/05 14:04:12 by rdestreb          #+#    #+#             */
/*   Updated: 2014/12/05 17:52:52 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_data	*init_list(void)
{
	static t_data	*lst = NULL;

	if(!lst)
		lst = (t_data *)ft_memalloc(sizeof(t_data));
	return (lst);
}

t_data	*add_link(char *name)
{
	t_data	*lst;
	t_data	*add;
	t_data	*tmp;

	lst = init_list();
	add = (t_data *)ft_memalloc(sizeof(t_data));
	add->name = ft_strdup(name);
	while (lst && lst->next && (ft_strcmp(add->name, lst->next->name) >= 0))
		lst = lst->next;
	tmp = lst->next;
	lst->next = add;
	add->next = tmp;
	return (lst);
}
