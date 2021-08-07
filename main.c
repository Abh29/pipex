#include "pipex.h"

static void	ft_init(t_data *data)
{
	if (data->argc != 5)
		ft_exit("Error : illigal number of arguments !", 1);
	if (pipe(data->p) < 0)
		ft_exit_errno("pipe Error : ", EPIPE);
	data->file1 = open(data->argv[1], O_RDONLY);
	if (data->file1 < 0)
	{
		perror("Error : ");
		exit(1);
	}
	data->file2 = open(data->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (data->file2 < 0)
	{
		perror("Error file2 : ");
		exit(1);
	}
	data->cmd1 = ft_split_cmd(data->argv[2], data->envp);
	data->cmd2 = ft_split_cmd(data->argv[3], data->envp);
	if (!data->cmd1 || !data->cmd2)
		ft_exit("Error : unexpected split error !",1);
	errno = 0;
}

static void	proc_1(t_data *data)
{
	char	**save;

	save = data->cmd1;
	data->pid1 = fork();
	if (data->pid1 < 0)
		ft_exit("Fork Error!", 3);
	if (data->pid1 == 0)
	{
		dup2(data->file1, STDIN_FILENO);
		close(data->p[0]);
		dup2(data->p[1], STDOUT_FILENO);
		close(data->p[1]);
		execve(data->cmd1[0], data->cmd1, data->envp);
		perror("Error in first process ");
		exit(3);
	}
	data->cmd1 = save;
}

static void	proc_2(t_data *data)
{
	char	**save;

	save = data->cmd2;
	data->pid2 = fork();
	if (data->pid2 < 0)
		ft_exit("Fork Error!", 3);
	if (data->pid2 == 0)
	{
		close(data->p[1]);
		dup2(data->file2, STDOUT_FILENO);
		close(data->file2);
		dup2(data->p[0], STDIN_FILENO);
		close(data->p[0]);
		execve(data->cmd2[0], data->cmd2, data->envp);
		perror("Error in second process ");
		exit(3);
	}
	data->cmd2 = save;
}

static void	ft_tidyup(t_data *data)
{
	close(data->p[0]);
	close(data->p[1]);
	waitpid(data->pid1, NULL, 0);
	waitpid(data->pid2, NULL, 0);
	close(data->file1);
	close(data->file2);
	ft_free_split(&(data->cmd1));
	ft_free_split(&(data->cmd2));
}

int main(int argc, char **argv, char **envp)
{
	t_data  data;

	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	ft_init(&data);
	proc_1(&data);
	proc_2(&data);
	ft_tidyup(&data);
	return (0);
}


/* 
this is a test main 

this is a nother test main 
*/