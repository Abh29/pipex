#include "../pipex.h"

void	ft_exit(char *str, int status)
{
	ft_putendl_fd(str, STDERR_FILENO);
	exit(status);
}

void	ft_exit_errno(char *str, int status)
{
	errno = status;
	perror(str);
}

/*
# define UNSUFFICIENT_ARGS_COUNT() ft_exit("Error : \
		more earguments expected !", -1);
# define PIPE_ERROR() ft_exit_errno("pipe Error : ", EPIPE);
# define MALLOC_ERROR() ft_exit_errno("malloc error : ", ENOMEM);
# define PERMISSION_ERROR() ft_exit_errno("Error : ", EACCES);
# define EXEC_ERROR() ft_exit_errno("Error : ", ENOEXEC);
# define ARGC_TOO_LONG() ft_exit_errno("Error : ", E2BIG);
# define FORK_ERROR() ft_exit_errno("Fork Error : ", EMVSINITIAL);
*/