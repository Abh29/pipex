#ifndef PIPEX_H
# define PIPEX_H

#include "libft/libft.h"
#include "gnl/get_next_line.h"
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

typedef struct  s_dpipe
{
    int va[2];
    int vien[2];
}               t_dpipe;

typedef static  s_cmdl
{
    char cmds[100][2];
}               t_cmdl

# define UNSUFFICIENT_ARGS_COUNT() ft_exit("Error : more earguments expected !", -1);
# define PIPE_ERROR() ft_exit_errno("pipe Error : ", EPIPE);
# define MALLOC_ERROR() ft_exit_errno("malloc error : ", ENOMEM);
# define PERMISSION_ERROR() ft_exit_errno("Error : ", EACCES);
# define EXEC_ERROR() ft_exit_errno("Error : ", ENOEXEC);
# define ARGC_TOO_LONG() ft_exit_errno("Error : ", E2BIG);
# define FORK_ERROR() ft_exit_errno("Fork Error : ", EMVSINITIAL);

void    ft_exit(char *str, int status);
void    ft_exit_errno(char *str, int status);

#endif
