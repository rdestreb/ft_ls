/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdestreb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 17:05:55 by rdestreb          #+#    #+#             */
/*   Updated: 2014/11/26 13:21:48 by rdestreb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		FT_LS_H
# define	FT_LS_H

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

typedef struct dirent t_dir;
typedef struct stat  t_stat;

#endif
