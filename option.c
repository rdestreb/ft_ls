/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/12 10:48:48 by rdestreb          #+#    #+#             */
/*   Updated: 2014/12/12 20:00:15 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_opt	*singleton(void)
{
	static t_opt *flag = NULL;

	if (flag)
		return (flag);
	flag = (t_opt *)ft_memalloc(sizeof(t_opt));
	return (flag);
}

t_opt	*arg_parser(int ac, char **av)
{
	int		i;
	t_opt	*flag;

	i = 0;
	flag = singleton();
	while (++i < ac && av[i][0] == '-' && av[i][1])
	{
		illegal_option(av[i]);
		flag->l = (ft_strchr(av[i], 'l') ? flag->l + 1 : flag->l);
		flag->rec = (ft_strchr(av[i], 'R') ? flag->rec + 1 : flag->rec);
		flag->a = (ft_strchr(av[i], 'a') ? flag->a + 1 : flag->a);
		flag->r = (ft_strchr(av[i], 'r') ? flag->r + 1 : flag->r);
		flag->t = (ft_strchr(av[i], 't') ? flag->t + 1 : flag->t);
		(flag->nb_opt)++;
	}
	return (flag);
}

void	illegal_option(char *arg)
{
	int	i;

	i = 0;
	while (arg[++i])
	{
		if (arg[i] != 'l' && arg[i] != 'R' && arg[i] != 'a' && arg[i] != 'r'
			&& arg[i] != 't')
		{
			ft_putstr_fd("ft_ls: illegal option -- ", 2);
			ft_putchar_fd(arg[i], 2);
			ft_putstr_fd("\nusage: ft_ls [-Ralrt] [file ...]\n", 2);
			exit(1);
		}
	}
}
