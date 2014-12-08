/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/05 14:04:12 by rdestreb          #+#    #+#             */
/*   Updated: 2014/12/08 16:09:28 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*t_lst	*init_list(int reset)
{
	static t_lst	*lst = NULL;

	if (reset)
		lst = NULL;
	if(!lst)
		lst = (t_lst *)ft_memalloc(sizeof(t_lst));
	return (lst);
}
*/
t_lst	*add_link(t_data *data, t_lst *lst)
{
	t_lst	*add;
	t_lst	*tmp;
	t_opt	*flag;

	flag = singleton();
	add = (t_lst *)ft_memalloc(sizeof(t_lst));
	add->data = data;
	if (flag->r)
	{
		while (lst && lst->next &&
				(ft_strcmp(add->data->name, lst->next->data->name) < 0))
			lst = lst->next;
	}
	else
	{
		while (lst && lst->next &&
				(ft_strcmp(add->data->name, lst->next->data->name) >= 0))
			lst = lst->next;
	}
	tmp = lst->next;
	lst->next = add;
	add->next = tmp;
	return (lst);
}

void	disp_list(t_lst *lst, t_lst *first, t_lst *last)
{
	t_opt	*flag;

	flag = singleton();
	if (last && flag->l)
	{
		ft_putstr("total ");
		ft_putnbr(last->data->nblock);
		ft_putstr("\n");
	}
	lst = first->next;
	while(lst)
	{
		print_infos(lst->data);
		lst = lst->next;
	}
}

/*
void	delete_list(t_lst *lst)
{

}
*/
