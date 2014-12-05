/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 17:05:55 by rdestreb          #+#    #+#             */
/*   Updated: 2014/12/05 17:52:26 by rdestreb         ###   ########.fr       */
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

struct	s_data
{
	int		link;
	char	*uid;
	char	*gid;
	int		size;
	char	*date;
	char	*name;
	t_data	*next;
//	t_data	*prev;
};

typedef struct dirent t_dir;
typedef struct stat  t_stat;

void	display(char * path, t_dir *file);
t_data	*init_list(void);
t_data	*add_link(char *name);


#endif
