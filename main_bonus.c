#include "pipex.h"

typedef struct s_bdata
{
	int		**pn;
	char	***cmdn;
	char	*pidn;
    int		argc;
    char	**argv;
    char	**envp;
    int		file1;
    int		file2;
	int		n;
}				t_bdata;

static void ft_initstruct(t_bdata *bdata)
{
	int i;

	i = 0;
	bdata->n = bdata->argc - 3;
	bdata->pn = malloc(bdata->n * sizeof(int *));
	bdata->pidn = malloc(bdata->n * sizeof(int));
	bdata->cmdn = malloc(bdata->n * sizeof(char *));
	if (!bdata->pn || !bdata->pidn || ! bdata->cmdn)
		ft_exit_errno("malloc error : ", ENOMEM);
	while (i < bdata->n)
	{
		bdata->pn[i] = malloc(2 * sizeof(int));
		if (!bdata->pn[i])
			ft_exit_errno("malloc error : ", ENOMEM); ///leak ?!
		if (pipe(bdata->pn[i]) < 0)
			ft_exit_errno("pipe Error : ", EPIPE);
		bdata->cmdn[i] = ft_split_cmd(bdata->argv[i + 2], bdata->envp);
		if (!bdata->cmdn[i])
			ft_exit("Error : unexpected split error !",1);
		i++;
	}
}

static void	ft_init(t_bdata *data)
{
    if (data->argc < 5)
        ft_exit("Error : more earguments expected ! !", 1);
	ft_initstruct(data);
	data->file1 = open(data->argv[1], O_RDONLY);
    if (data->file1 < 0)
    {
        perror("Error : ");
        exit(1);
    }
    data->file2 = open(data->argv[data->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0755);
    if (data->file2 < 0)
    {
        perror("Error file2 : ");
        exit(1);
    }

	errno = 0;
}

static void ft_close_fd(t_bdata *data)
{
	int	i;

	i = 0;
	ft_putstr_fd("this is close \n", 2);
	while (i < data->n)
	{
		close(data->pn[i][0]);
		close(data->pn[i][1]);
	}
}

static void	proc1(t_bdata *data)
{
	char **save;

	save = data->cmdn[0];
	data->pidn[0] = fork();
    if (data->pidn[0] < 0)
        ft_exit("Fork Error! : proc 1", 3);
    if (data->pidn[0] == 0)
    {
        dup2(data->file1, STDIN_FILENO);
        dup2(data->pn[0][1], STDOUT_FILENO);
		ft_close_fd(data);
       	execve(data->cmdn[0][0], data->cmdn[0], data->envp);
        perror("Error in first process ");
       	exit(3);
    }
	data->cmdn[0] = save;
}

static void	proci(t_bdata *data, int i)
{
	data->pidn[i] = fork();
    if (data->pidn[i] < 0)
        ft_exit("Fork Error!", 3);
    if (data->pidn[i] == 0)
    {
        dup2(data->pn[i - 1][0], STDIN_FILENO);
        dup2(data->pn[i][1], STDOUT_FILENO);
		ft_close_fd(data);
       	execve(data->cmdn[i][0], data->cmdn[i], data->envp);
        perror("Error in first process ");
       	exit(3);
    }
}


static void procn(t_bdata *data, int n)
{
	data->pidn[n] = fork();
    if (data->pidn[n] < 0)
        ft_exit("Fork Error!", 3);
    if (data->pidn[n] == 0)
    {
        dup2(data->file2, STDOUT_FILENO);
        dup2(data->pn[n - 1][0], STDIN_FILENO);
        ft_close_fd(data);
       	execve(data->cmdn[n][0], data->cmdn[n], data->envp);
        perror("Error in second process ");
     	exit(3);
    }
}

static void	ft_tidyup(t_bdata *data)
{
	int i;
	int pid;

	i = 0;
	ft_close_fd(data);
	wait(NULL);
	printf("after waiting !");
	while (i < data->n)
	{
		ft_free_split(&(data->cmdn[i]));
		i++;
	}
	free(data->cmdn);
	data->cmdn = NULL;
	free(data->pn);
	data->pn = NULL;
	free(data->pidn);
	data->pidn = NULL;
	close(data->file1);
	close(data->file2);
}

int main(int argc, char **argv, char **envp)
{
    t_bdata  data;
	int		i;

	i = 1;
    data.argc = argc;
    data.argv = argv;
    data.envp = envp;
	ft_init(&data);

	
	for (size_t i = 0; i < data.n; i++)
	{
		for (size_t j = 0; data.cmdn[i][j] != NULL ; j++)
		{
			printf("%s\n",data.cmdn[i][j]);
		}
		printf("\n");
	}

	for (size_t i = 0; i < data.n; i++)
	{
		printf("%d  %d \n",data.pn[i][0], data.pn[i][1]);
	}

	for (size_t i = 0; i < data.n; i++)
	{
		printf("%d\n", data.pidn[i]);
	}
	
	
	
	proc1(&data);
	while (i < data.n -1)
		proci(&data, i++);
	procn(&data, i);
	ft_tidyup(&data);
    return (0);
}
