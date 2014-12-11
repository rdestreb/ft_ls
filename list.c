/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/05 14:04:12 by rdestreb          #+#    #+#             */
/*   Updated: 2014/12/11 20:51:39 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_lst	*tri(t_lst *lst, t_lst *add)
{
	t_opt	*flag;

	flag = singleton();
	if (flag->t)
	{
		while ((flag->r && lst && lst->next &&
				add->data->p_stat->st_mtime > lst->next->data->p_stat->st_mtime)
				|| (!(flag->r) && lst && lst->next &&
					add->data->p_stat->st_mtime
					<= lst->next->data->p_stat->st_mtime))
			lst = lst->next;
	}
	else
	{
		while ((!(flag->r) && lst && lst->next &&
				(ft_strcmp(add->data->name, lst->next->data->name) > 0)) ||
				(flag->r && lst && lst->next &&
				(ft_strcmp(add->data->name, lst->next->data->name) <= 0)))
			lst = lst->next;
	}
	return (lst);
}

t_lst	*add_link(t_data *data, t_lst *lst)
{
	t_lst	*add;
	t_lst	*tmp;

	add = (t_lst *)ft_memalloc(sizeof(t_lst));
	add->data = data;
	lst = tri(lst, add);
	tmp = lst->next;
	lst->next = add;
	add->next = tmp;
	return (lst);
}

void	disp_list(t_lst *lst, t_lst *first, int *nblock, t_max *max)
{
	t_opt	*flag;

	flag = singleton();
	if (flag->l)
	{
		ft_putstr("total ");
		ft_putnbr(*nblock);
		ft_putstr("\n");
	}
	lst = first->next;
	while (lst)
	{
		if (flag->a ||
			(!(flag->a) && ft_strncmp(lst->data->file->d_name, ".", 1)))
			print_infos(lst->data, max);
		lst = lst->next;
	}
	delete_list(lst);
}

void	delete_list(t_lst *lst)
{
	if (!lst)
		return ;
	if (lst->next)
		delete_list(lst->next);
	if (lst->data)
	{
		free(lst->data->link);
		free(lst->data->gid);
		free(lst->data->uid);
		free(lst->data->size);
		free(lst->data->date);
		free(lst->data->name);
		free(lst->data->file);
		free(lst->data->p_stat);
		free(lst->data);
	}
	free(lst->path);
	free(lst);
}
