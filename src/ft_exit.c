#include "../pipex.h"

void    ft_exit(char *str, int status)
{
    ft_putendl_fd(str, STDERR_FILENO);
    exit(status);
}

void    ft_exit_errno(char *str, int status)
{
    errno = status;
    perror(str);
}
