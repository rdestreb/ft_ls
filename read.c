/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/12 10:49:03 by rdestreb          #+#    #+#             */
/*   Updated: 2014/12/12 10:49:07 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	read_dir(char *path)
{
	DIR		*dir;
	t_dir	*file;
	t_lst	*lst;
	int		nblock;
	t_opt	*flag;

	flag = singleton();
	nblock = 0;
	if (!(dir = opendir(path)))
		return (print_error(path));
	lst = (t_lst *)ft_memalloc(sizeof(t_lst));
	while ((file = readdir(dir)))
	{
		if (flag->a || (!(flag->a) && ft_strncmp(file->d_name, ".", 1)))
			display(path, file, lst, &nblock);
		else if (flag->rec && ft_strcmp(file->d_name, "..") &&
				ft_strcmp(file->d_name, "."))
			display(path, file, lst, &nblock);
	}
	if (closedir(dir) != 0)
		return (print_error(""));
	read_list(lst, path, &nblock);
}

void	display(char *path, t_dir *file, t_lst *lst, int *nblock)
{
	t_stat	*p_stat;
	char	*path2;

	if (!(p_stat = (t_stat *)ft_memalloc(sizeof(t_stat))))
		return ;
	path2 = ft_strjoin(ft_strjoin(path, "/"), file->d_name);
	lst->path = path2;
	if (file->d_type == DT_LNK)
		lstat(path2, p_stat);
	else
		stat(path2, p_stat);
	get_infos(p_stat, file, lst, nblock);
	ft_strdel(&path2);
}

void	recursive(t_lst *lst, char *path, t_lst *first)
{
	t_dir	*file;
	char	*path2;

	lst = first->next;
	while (lst)
	{
		file = lst->data->file;
		if (file->d_type == DT_DIR && ft_strcmp(lst->data->name, ".") &&
			ft_strcmp(lst->data->name, ".."))
		{
			path2 = ft_strjoin(ft_strjoin(path, "/"), lst->data->name);
			ft_putendl(ft_strjoin(ft_strjoin("\n", path2), ":"));
			read_dir(path2);
			ft_strdel(&path2);
		}
		lst = lst->next;
	}
}
