#include "../pipex.h"

void    ft_exit(char *str, int status)
{
    perror(str);
    exit(status);
}