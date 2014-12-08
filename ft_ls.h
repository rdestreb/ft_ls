/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 17:05:55 by rdestreb          #+#    #+#             */
/*   Updated: 2014/12/08 12:08:18 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		FT_LS_H
# define	FT_LS_H

# define TRUE 1
# define FALSE 0

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

typedef struct	s_opt
{
	int	l;
	int	rec;
	int	a;
	int	r;
	int	t;
	int nb_opt;
}				t_opt;

typedef struct s_data t_data;
typedef struct s_lst t_lst;
typedef struct dirent t_dir;
typedef struct stat  t_stat;

struct	s_data
{
	int		link;
	int		nblock;
	char	*uid;
	char	*gid;
	int		size;
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


void	display(char * path, t_dir *file, t_lst *lst);
t_opt	*singleton(void);
void	print_infos(t_data *p_data);
t_lst	*add_link(t_data *data, t_lst *lst);
void	disp_list(t_lst *lst, t_lst *first, t_lst *last);
void	read_list(t_lst *lst, char *path);



#endif
