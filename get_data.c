/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/12 10:49:40 by rdestreb          #+#    #+#             */
/*   Updated: 2014/12/12 19:52:19 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_link(t_stat *p_stat, t_dir *file, t_lst *lst, t_data *p_data)
{
	char	*link;
	int		ret;
	t_opt	*flag;

	flag = singleton();
	if (!(link = (char *)ft_memalloc(sizeof(char) * p_stat->st_size + 2)))
		return (print_error(""));
	if ((ret = readlink(lst->path, link, p_stat->st_size + 1)) == -1)
		return (print_error(""));
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
	if (ft_strcmp(lst->data->maj, "0") && max->m_maj < ft_strlen(lst->data->maj))
		max->m_maj = ft_strlen(lst->data->maj);
	if (ft_strcmp(lst->data->min, "0") && max->m_min < ft_strlen(lst->data->min))
		max->m_min = ft_strlen(lst->data->min);
}
