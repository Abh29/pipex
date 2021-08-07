#include "../pipex.h"


void	proc0(t_bdata *data)
{
	int		pid;
	char	*line;

	pid = fork();
	if (pid < 0)
		ft_exit("Fork Error: : proc 0", 3);
	if (pid == 0)
	{
		while (1)
		{
			ft_putstr_fd("> ", STDOUT_FILENO);
			line = get_next_line(STDIN_FILENO);
			if (!line || ft_strcmp(data->lim, line))
				break ;
			ft_putstr_fd(line, data->pn[0][1]);
			free(line);
		}
		free(line);
		line = NULL;
		ft_close_fd(data);
		exit(0);
	}
}

void	proc1(t_bdata *data)
{
	int pid;

	pid = fork();
    if (pid < 0)
        ft_exit("Fork Error! : proc 1", 3);
    if (pid == 0)
    {
        dup2(data->file1, STDIN_FILENO);
        dup2(data->pn[0][1], STDOUT_FILENO);
		ft_close_fd(data);
       	execve(data->cmdn[0][0], data->cmdn[0], data->envp);
        perror("Error in first process ");
       	exit(3);
    }
}

void	proci(t_bdata *data, int i)
{
	int	pid;

	pid = fork();
    if (pid < 0)
        ft_exit("Fork Error!", 3);
    if (pid == 0)
    {
        dup2(data->pn[i - 1][0], STDIN_FILENO);
        dup2(data->pn[i][1], STDOUT_FILENO);
		ft_close_fd(data);
       	execve(data->cmdn[i][0], data->cmdn[i], data->envp);
        perror("Error in process exec ");
       	exit(3);
    }
}

void	procn(t_bdata *data, int n)
{
	int pid;

	pid = fork();
    if (pid < 0)
        ft_exit("Fork Error!", 3);
    if (pid == 0)
    {
        dup2(data->file2, STDOUT_FILENO);
        dup2(data->pn[n - 1][0], STDIN_FILENO);
        ft_close_fd(data);
       	execve(data->cmdn[n][0], data->cmdn[n], data->envp);
        perror("Error in last process ");
     	exit(3);
    }
}
