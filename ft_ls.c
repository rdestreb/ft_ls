/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 10:13:32 by rdestreb          #+#    #+#             */
/*   Updated: 2014/12/11 20:33:45 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

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

void	get_permission(int path, t_dir *file)
{
	if (file->d_type == DT_LNK)
		ft_putstr("l");
	else if (file->d_type == DT_FIFO)
		ft_putstr("p");
	else if (file->d_type == DT_SOCK)
		ft_putstr("s");
	else if (file->d_type == DT_BLK)
		ft_putstr("b");
	else if (file->d_type == DT_CHR)
		ft_putstr("c");
	else if (file->d_type == DT_DIR)
		ft_putstr("d");
	else
		ft_putstr("-");
	ft_putstr((path & S_IRUSR) ? "r" : "-");
	ft_putstr((path & S_IWUSR) ? "w" : "-");
	ft_putstr((path & S_IXUSR) ? "x" : "-");
	ft_putstr((path & S_IRGRP) ? "r" : "-");
	ft_putstr((path & S_IWGRP) ? "w" : "-");
	ft_putstr((path & S_IXGRP) ? "x" : "-");
	ft_putstr((path & S_IROTH) ? "r" : "-");
	ft_putstr((path & S_IWOTH) ? "w" : "-");
	ft_putstr((path & S_IXOTH) ? "x" : "-");
	ft_putstr(" ");
}

char	*cleaning(char *path)
{
	char	*tmp;

	tmp = path;
	path = ft_strjoin(" ", path);
	free(tmp);
	return (path);
}

void	padding2(t_data *p_data, t_max *max)
{
	if (p_data->file->d_type == DT_BLK || p_data->file->d_type == DT_CHR)
	{
		while (ft_strlen(p_data->maj) <= max->m_maj + 1)
			p_data->maj = ft_strjoin(" ", p_data->maj);
		ft_putstr(p_data->maj);
		ft_putstr(",");
		while (ft_strlen(p_data->min) <= max->m_min)
			p_data->min = ft_strjoin(" ", p_data->min);
		ft_putstr(p_data->min);
	}
	else
	{
		while (ft_strlen(p_data->size) < max->m_size + max->m_min + max->m_maj)
			p_data->size = ft_strjoin(" ", p_data->size);
		ft_putstr(p_data->size);
	}
}

void	padding(t_data *p_data, t_max *max)
{
	while (ft_strlen(p_data->link) <= max->m_link)
		p_data->link = ft_strjoin(" ", p_data->link);
	ft_putstr(p_data->link);
	ft_putstr(" ");
	while (ft_strlen(p_data->uid) <= max->m_uid + 1)
		p_data->uid = ft_strjoin(p_data->uid, " ");
	ft_putstr(p_data->uid);
	while (ft_strlen(p_data->gid) < max->m_gid)
		p_data->gid = ft_strjoin(p_data->gid, " ");
	ft_putstr(p_data->gid);
}

void	print_infos(t_data *p_data, t_max *max)
{
	t_opt	*flag;

	flag = singleton();
	if (flag->l)
	{
		get_permission(p_data->p_stat->st_mode, p_data->file);
		padding(p_data, max);
		padding2(p_data, max);
		ft_putstr(p_data->date);
		ft_putstr(" ");
	}
	ft_putendl(p_data->name);
}

void	get_link(t_stat *p_stat, t_dir *file, t_lst *lst, t_data *p_data)
{
	char	*link;
	int		ret;
	t_opt	*flag;

	flag = singleton();
	if (!(link = (char *)ft_memalloc(sizeof(int) * p_stat->st_size + 1)))
		return (print_error(""));
	if ((ret = readlink(lst->path, link, p_stat->st_size + 1)) == -1)
		return (print_error(""));
	link[p_stat->st_size + 1] = 0;
	if (flag->l)
		p_data->name = ft_strjoin(ft_strjoin(file->d_name, " -> "), link);
	else
		p_data->name = ft_strdup(file->d_name);
}

void	get_time(t_stat *p_stat, t_data *p_data)
{
	char	*t_f;
	time_t	t;

	t = time(NULL);
	t_f = ctime(&p_stat->st_mtime);
	if (t < (p_stat->st_mtime) || (t > (p_stat->st_mtime) + 15778463))
		p_data->date = ft_strjoin(ft_strsub(t_f, 3, 8), ft_strsub(t_f, 19, 5));
	else
		p_data->date = ft_strsub(t_f, 3, 13);
}

void	get_id(t_stat *p_stat, t_data *p_data)
{
	if (!(getpwuid(p_stat->st_uid)))
		p_data->uid = ft_itoa(p_stat->st_uid);
	else
		p_data->uid = getpwuid(p_stat->st_uid)->pw_name;
	if (!(getgrgid(p_stat->st_gid)))
		p_data->gid = ft_itoa(p_stat->st_gid);
	else
		p_data->gid = getgrgid(p_stat->st_gid)->gr_name;
}

void	get_infos(t_stat *p_stat, t_dir *file, t_lst *lst, int *nblock)
{
	t_data		*p_data;

	if (!(p_data = (t_data *)ft_memalloc(sizeof(t_data))))
		return ;
	*nblock += p_stat->st_blocks;
	p_data->link = ft_itoa(p_stat->st_nlink);
	get_id(p_stat, p_data);
	p_data->size = ft_itoa(p_stat->st_size);
	get_time(p_stat, p_data);
	if (file->d_type == DT_LNK)
		get_link(p_stat, file, lst, p_data);
	else
		p_data->name = ft_strdup(file->d_name);
	p_data->p_stat = p_stat;
	p_data->maj = ft_itoa(major(p_data->p_stat->st_rdev));
	p_data->min = ft_itoa(minor(p_data->p_stat->st_rdev));
	p_data->file = file;
	p_data->file = (t_dir *)ft_memalloc(sizeof(t_dir));
	ft_memcpy(p_data->file, file, sizeof(t_dir));
	add_link(p_data, lst);
}

void	read_dir(char *path)
{
	DIR		*dir;
	t_dir	*file;
	t_lst	*lst;
	int		nblock;

	nblock = 0;
	if (!(dir = opendir(path)))
		return (print_error(path));
	lst = (t_lst *)ft_memalloc(sizeof(t_lst));
	while ((file = readdir(dir)))
		display(path, file, lst, &nblock);
	if (closedir(dir) != 0)
		return (print_error(""));
	read_list(lst, path, &nblock);
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

void	get_max(t_lst *lst, t_max *max)
{
	if (max->m_uid < ft_strlen(lst->data->uid))
		max->m_uid = ft_strlen(lst->data->uid);
	if (max->m_gid < ft_strlen(lst->data->gid))
		max->m_gid = ft_strlen(lst->data->gid);
	if (max->m_link < ft_strlen(lst->data->link))
		max->m_link = ft_strlen(lst->data->link);
	if (max->m_size < ft_strlen(lst->data->size))
		max->m_size = ft_strlen(lst->data->size);
	if (max->m_maj < ft_strlen(lst->data->maj))
		max->m_maj = ft_strlen(lst->data->maj);
	if (max->m_min < ft_strlen(lst->data->min))
		max->m_min = ft_strlen(lst->data->min);
}

void	read_list(t_lst *lst, char *path, int *nblock)
{
	t_opt	*flag;
	t_lst	*first;
	t_max	*max;

	flag = singleton();
	max = (t_max *)ft_memalloc(sizeof(t_max));
	first = lst;
	lst = lst->next;
	while (lst)
	{
		get_max(lst, max);
		lst = lst->next;
	}
	disp_list(lst, first, nblock, max);
	if (flag->rec)
		recursive(lst, path, first);
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

t_arg	*init_tri_arg(void)
{
	static t_arg *lst = NULL;

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
	static int	cpt = 0;

	flag = singleton();
	cpt++;
	add = (t_arg *)ft_memalloc(sizeof(t_arg));
	add->arg = ft_strdup(arg);
	add->cpt = cpt;
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

int	main(int ac, char **av)
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
	return (0);
}
