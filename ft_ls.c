/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 10:13:32 by rdestreb          #+#    #+#             */
/*   Updated: 2014/11/26 21:19:45 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_error(void)
{
	perror("Error ");
	exit (1);
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
			ft_putendl(file->d_name);
			ft_putendl((char *)&file->d_type);
			stat(file->d_name, info);
			//ft_putstr(ctime(&info->st_atime));
			//ft_putstr(ctime(&info->st_ctime));
			ft_putstr(ctime(&info->st_mtime));
			ft_putendl(getpwuid(info->st_uid)->pw_name);
			ft_putendl(getgrgid(info->st_gid)->gr_name);
			//ft_putendl()
		}
	}
	if (closedir(dir) !=0)
		print_error();
	return (0);
}
