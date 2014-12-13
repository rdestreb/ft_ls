/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 10:13:32 by rdestreb          #+#    #+#             */
/*   Updated: 2014/12/12 15:16:25 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_arg	*init_tri_arg(void)
{
	static t_arg	*lst = NULL;

	if (!lst)
		lst = (t_arg *)ft_memalloc(sizeof(t_arg));
	return (lst);
}

t_arg	*tri_arg(char *arg)
{
	t_arg		*lst;
	t_arg		*add;
	t_arg		*tmp;
	t_opt		*flag;

	flag = singleton();
	add = (t_arg *)ft_memalloc(sizeof(t_arg));
	add->arg = ft_strdup(arg);
	lst = init_tri_arg();
	if (!(flag->r))
		while (lst && lst->next && ft_strcmp(add->arg, lst->next->arg) > 0)
			lst = lst->next;
	else
		while (lst && lst->next && ft_strcmp(add->arg, lst->next->arg) <= 0)
			lst = lst->next;
	tmp = lst->next;
	lst->next = add;
	add->next = tmp;
	return (lst);
}

void	disp_arg(t_arg *p_arg, int ac, char **av, int nb_arg)
{
	t_opt	*flag;

	flag = singleton();
	while (ac-- > 1 && ac > flag->nb_opt)
		p_arg = tri_arg(av[ac]);
	p_arg = init_tri_arg();
	p_arg = p_arg->next;
	while (p_arg)
	{
		if (nb_arg > 1)
			ft_putendl(ft_strjoin(p_arg->arg, ":"));
		read_dir(p_arg->arg);
		if (p_arg->next)
			ft_putstr("\n");
		p_arg = p_arg->next;
	}
}

void	delete_arg(t_arg *lst)
{
	if (!lst)
		return ;
	if (lst->next)
		delete_arg(lst);
	if (lst->arg)
		free(lst->arg);
	free(lst);
}

int		main(int ac, char **av)
{
	t_opt	*flag;
	t_arg	*p_arg;
	int		nb_arg;

	flag = arg_parser(ac, av);
	if (!(p_arg = (t_arg *)ft_memalloc(sizeof(t_arg))))
		return (0);
	nb_arg = ac - flag->nb_opt - 1;
	if (ac == (flag->nb_opt + 1))
		read_dir(".");
	else
		disp_arg(p_arg, ac, av, nb_arg);
	delete_arg(p_arg);
	return (0);
}
