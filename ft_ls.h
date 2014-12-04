/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 17:05:55 by rdestreb          #+#    #+#             */
/*   Updated: 2014/12/04 15:02:02 by rdestreb         ###   ########.fr       */
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
# include "libft/includes/libft.h"

typedef struct	s_opt
{
	int	l;
	int	rec;
	int	a;
	int	r;
	int	t;
	int nb_opt;
}				t_opt;

typedef struct dirent t_dir;
typedef struct stat  t_stat;

void	display(char * path, t_dir *file);

#endif
