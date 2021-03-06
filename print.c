/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/12 10:49:18 by rdestreb          #+#    #+#             */
/*   Updated: 2014/12/14 11:11:33 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void	padding_size(t_data *p_data, t_max *max)
{
	char	*tmp;

	while (ft_strlen(p_data->size) <= max->m_size + 1 ||
			(max->m_maj && ft_strlen(p_data->size) <=
				max->m_min + max->m_maj + 3))
	{
		tmp = p_data->size;
		p_data->size = ft_strjoin(" ", p_data->size);
		free(tmp);
	}
	ft_putstr(p_data->size);
}

void	padding2(t_data *p_data, t_max *max)
{
	char	*tmp;

	if (p_data->file->d_type == DT_BLK || p_data->file->d_type == DT_CHR)
	{
		while (ft_strlen(p_data->maj) <= max->m_maj + 1)
		{
			tmp = p_data->maj;
			p_data->maj = ft_strjoin(" ", p_data->maj);
			free(tmp);
		}
		ft_putstr(p_data->maj);
		ft_putstr(",");
		while (ft_strlen(p_data->min) <= max->m_min)
		{
			tmp = p_data->min;
			p_data->min = ft_strjoin(" ", p_data->min);
			free(tmp);
		}
		ft_putstr(p_data->min);
	}
	else
		padding_size(p_data, max);
}

void	padding(t_data *p_data, t_max *max)
{
	char	*tmp;

	while (ft_strlen(p_data->link) <= max->m_link)
	{
		tmp = p_data->link;
		p_data->link = ft_strjoin(" ", p_data->link);
		free(tmp);
	}
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
	if (p_data->file->d_type == DT_DIR)
		ft_putstr(CYAN);
	else if (p_data->file->d_type == DT_BLK)
		ft_putstr(B_CYAN);
	else if (p_data->file->d_type == DT_CHR)
		ft_putstr(B_YELLOW);
	else if (p_data->file->d_type == DT_LNK)
		ft_putstr(MAGENTA);
	else if (p_data->p_stat->st_mode & S_IXUSR ||
				(p_data->p_stat->st_mode & S_IXGRP) ||
				(p_data->p_stat->st_mode & S_IXOTH))
		ft_putstr(RED);
	ft_putstr(p_data->name);
	ft_putstr(BLANK);
}
