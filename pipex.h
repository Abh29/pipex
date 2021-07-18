#ifndef PIPEX_H
# define PIPEX_H

#include "libft/libft.h"
#include "gnl/get_next_line.h"
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct s_dpipe
{
    int va[2];
    int vien[2];
}               t_dpipe;


void    ft_exit(char *str, int status);

#endif