/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 10:13:32 by rdestreb          #+#    #+#             */
/*   Updated: 2014/11/27 19:37:30 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_error(void)
{
	perror("Error ");
	exit (1);
}

t_opt	*arg_parser(int ac, char **av)
{
	int		i;
	t_opt	*flag;

	i = -1;
	flag = (t_opt *)ft_memalloc(sizeof(t_opt));
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			flag->l = (ft_strchr(av[i], 'l') ? flag->l + 1 : flag->l);
			flag->rec = (ft_strchr(av[i], 'R') ? flag->rec + 1 : flag->rec);
			flag->a = (ft_strchr(av[i], 'a') ? flag->a + 1 : flag->a);
			flag->r = (ft_strchr(av[i], 'r') ? flag->r + 1 : flag->r);
			flag->t = (ft_strchr(av[i], 't') ? flag->t + 1 : flag->t);
		}
	}
	return (flag);
}

void	get_infos(t_stat *info, t_dir *file)
{
	ft_putstr(" ");
	ft_putnbr(info->st_nlink);
	ft_putstr(" ");
	ft_putstr(getpwuid(info->st_uid)->pw_name);
	ft_putstr(" ");
	ft_putstr(getgrgid(info->st_gid)->gr_name);
	ft_putstr(" ");
	ft_putnbr(info->st_size);
	ft_putstr(" ");
	ft_putstr(ft_strsub(ctime(&info->st_mtime), 4, 12));
	ft_putstr(" ");
	ft_putendl(file->d_name);
}

void	get_permission(int path)
{
	ft_putstr(S_ISDIR(path) ? "d" : "-");
	ft_putstr((path & S_IRUSR) ? "r" : "-");
	ft_putstr((path & S_IWUSR) ? "w" : "-");
	ft_putstr((path & S_IXUSR) ? "x" : "-");
	ft_putstr((path & S_IRGRP) ? "r" : "-");
	ft_putstr((path & S_IWGRP) ? "w" : "-");
	ft_putstr((path & S_IXGRP) ? "x" : "-");
	ft_putstr((path & S_IROTH) ? "r" : "-");
	ft_putstr((path & S_IWOTH) ? "w" : "-");
	ft_putstr((path & S_IXOTH) ? "x" : "-");
}

int	main(int ac, char **av)
{
	DIR		*dir;
	t_dir	*file;
	t_stat	info[100];
	t_opt	*flag;
//	struct stat	info;

	flag = arg_parser(ac, av);
	ft_putnbr(flag->l);
	ft_putnbr(flag->rec);
	ft_putnbr(flag->a);
	ft_putnbr(flag->r);
	ft_putnbr(flag->t);
	if (ac == 1)
		dir = opendir(".");
	else
	{
		if (!(dir = opendir(av[1])))
			print_error();
	}
	while ((file = readdir(dir)))
	{
		if (ft_strncmp(file->d_name , ".", 1) != 0)
		{
			if(stat(file->d_name, info) == -1)
				print_error();
			get_permission(info->st_mode);
			get_infos(info, file);
			//ft_putstr(file->d_name);
			//	ft_putstr("\n");

		}
	}
	if (closedir(dir) !=0)
		print_error();
	return (0);
}
