/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 10:13:32 by rdestreb          #+#    #+#             */
/*   Updated: 2014/11/27 13:15:28 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_error(void)
{
	perror("Error ");
	exit (1);
}

/*int	arg_parser(int ac, char **av)
{
	t_opt	*flag;
	int		i;
	int		j;

	i = -1;
	while (++i < argc)
	{
		if (argv[i][0] == '-')
		{
			j = -1;
			while (argv[i][++j])
			{
				if (argv[i][j] == 'l')
					flag->l = TRUE;
			}
		}
	}
}*/

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
	t_stat	info[50];
//	struct stat	info;

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

			ft_putstr("\n");
			ft_putendl(file->d_name);

			get_permission(info->st_mode);

			ft_putnbr(info->st_nlink);
			ft_putstr("\n");
			ft_putendl(getpwuid(info->st_uid)->pw_name);
			ft_putendl(getgrgid(info->st_gid)->gr_name);
			ft_putnbr(info->st_size);
			ft_putstr("\n");
			ft_putstr(ctime(&info->st_mtime));
		}
	}
	if (closedir(dir) !=0)
		print_error();
	return (0);
}
