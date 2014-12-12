/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 17:05:55 by rdestreb          #+#    #+#             */
/*   Updated: 2014/12/12 15:16:23 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include <sys/stat.h>
# include <uuid/uuid.h>
# include <dirent.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include "libft/libft.h"

typedef struct s_opt	t_opt;
typedef struct s_max	t_max;
typedef struct s_data	t_data;
typedef struct s_lst	t_lst;
typedef struct s_tm		t_time;
typedef struct dirent	t_dir;
typedef struct stat		t_stat;
typedef struct s_arg	t_arg;

struct	s_opt
{
	int	l;
	int	rec;
	int	a;
	int	r;
	int	t;
	int nb_opt;
};

struct	s_max
{
	u_int	m_link;
	u_int	m_uid;
	u_int	m_gid;
	u_int	m_size;
	u_int	m_maj;
	u_int	m_min;
};

struct	s_data
{
	char	*link;
	char	*uid;
	char	*gid;
	char	*size;
	char	*maj;
	char	*min;
	char	*date;
	char	*name;
	t_dir	*file;
	t_stat	*p_stat;
};

struct	s_lst
{
	char	*path;
	t_data	*data;
	t_lst	*next;
};

struct	s_arg
{
	char	*arg;
	t_arg	*next;
};

t_arg	*init_tri_arg(void);
t_arg	*tri_arg(char *arg);
void	disp_arg(t_arg *p_arg, int ac, char **av, int nb_arg);
void	read_dir(char *path);
void	recursive(t_lst *lst, char *path, t_lst *first);
void	display(char *path, t_dir *file, t_lst *lst, int *nblock);
t_opt	*singleton(void);
t_opt	*arg_parser(int ac, char **av);
void	illegal_option(char *arg);
void	get_link(t_stat *p_stat, t_dir *file, t_lst *lst, t_data *p_data);
void	get_time(t_stat *p_stat, t_data *p_data);
void	get_id(t_stat *p_stat, t_data *p_data);
void	get_infos(t_stat *p_stat, t_dir *file, t_lst *lst, int *nblock);
void	get_max(t_lst *lst, t_max *max);
void	print_infos(t_data *p_data, t_max *max);
void	padding(t_data *p_data, t_max *max);
void	padding2(t_data *p_data, t_max *max);
void	get_permission(int path, t_dir *file);
void	print_error(char *error);
void	print_infos(t_data *p_data, t_max *max);
t_lst	*add_link(t_data *data, t_lst *lst);
t_lst	*tri(t_lst *lst, t_lst *add);
void	disp_list(t_lst *lst, t_lst *first, int *block, t_max *max);
void	read_list(t_lst *lst, char *path, int *block);
void	delete_list(t_lst *lst);

#endif
