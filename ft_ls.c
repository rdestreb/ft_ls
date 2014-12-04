/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 10:13:32 by rdestreb          #+#    #+#             */
/*   Updated: 2014/12/04 16:24:56 by rdestreb         ###   ########.fr       */
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


void	print_error(char *error)
{
	ft_putstr_fd("ft_ls: ", 2);
	perror(error);
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

t_opt	*arg_parser(int ac, char **av)
{
	int		i;
	t_opt	*flag;

	i = 0;
	flag = singleton();
	while (++i < ac && av[i][0] == '-')
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

void	get_infos(t_stat *info, t_dir *file)
{
//	static int	nb_blocks;
	t_opt	*flag;

	flag = singleton();
	if (flag->l)
	{
//		nb_blocks =+ info->st_blocks;
		//	ft_putnbr(nb_blocks);
		get_permission(info->st_mode);
		ft_putstr(" ");
		ft_putnbr(info->st_nlink);
		ft_putstr(ft_strjoin(" ", getpwuid(info->st_uid)->pw_name));
		ft_putstr(ft_strjoin(" ", getgrgid(info->st_gid)->gr_name));
		ft_putstr(ft_strjoin(" ", ft_itoa(info->st_size)));
		ft_putstr(ft_strjoin(" ", ft_strsub(ctime(&info->st_mtime), 4, 12)));
		ft_putstr(" ");
	}
	ft_putendl(file->d_name);
}

void	read_dir(char *path)
{
	DIR		*dir;
	t_dir	*file;
	t_opt	*flag;

	flag = singleton();
	if (!(dir = opendir(path)))
		return (print_error(path));
	while ((file = readdir(dir)))
	{
		if (flag->a || (!(flag->a) && ft_strncmp(file->d_name , ".", 1)))
			display(path, file);
		else if(flag->rec && ft_strcmp(file->d_name , ".")
				&& ft_strcmp(file->d_name, ".."))
				display(path, file);
	}
	if (closedir(dir) != 0)
		return (print_error(""));
}

void	display(char * path, t_dir *file)
{
	t_stat	*info;
	char	*path2;
	t_opt	*flag;

	if(!(info = (t_stat *)ft_memalloc(sizeof(t_stat))))
		return ;
	flag = singleton();
	path2 = ft_strjoin(ft_strjoin(path, "/"), file->d_name);
	stat(path2, info);
	get_infos(info, file);
	if (flag->rec && file->d_type == DT_DIR
		&& ft_strcmp(file->d_name , ".") && ft_strcmp(file->d_name, ".."))
	{
		//ft_putendl("");
		ft_putendl(ft_strjoin("\n",path2));
		//	flag->a = 1;
		read_dir(path2);
	}
	ft_strdel(&path2);
}

int	main(int ac, char **av)
{
	t_opt	*flag;

	flag = arg_parser(ac, av);

/*	ft_putnbr(flag->l);
	ft_putnbr(flag->rec);
	ft_putnbr(flag->a);
	ft_putnbr(flag->r);
	ft_putnbr(flag->t);
	ft_putstr("\n");
	ft_putnbr(flag->nb_opt);
*/
	if (ac == (flag->nb_opt + 1))
		read_dir(".");
	else
	{
		while(ac-- > 1 && (ac > flag->nb_opt))
			read_dir(av[ac]);
	}
	return (0);
}



