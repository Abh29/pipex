/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:52:54 by mehill            #+#    #+#             */
/*   Updated: 2021/10/13 20:54:13 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_initstruct(t_bdata *bdata)
{
	int	i;
	int	ofst;

	i = 0;
	ofst = 2;
	if (bdata->lim)
		ofst = 3;
	bdata->n = bdata->argc - ofst - 1;
	while (i < bdata->n)
	{
		if (pipe(bdata->pn[i]) < 0)
			ft_exit_errno("pipe Error : ", EPIPE);
		bdata->cmdn[i] = ft_split_cmd(bdata->argv[i + ofst], bdata->envp);
		if (!bdata->cmdn[i])
			ft_exit("Error : unexpected split error !", 1);
		i++;
	}
}

static void	ft_init_suit(t_bdata *data)
{
	if (!data->lim && data->file1 < 0)
	{
		perror("Error : ");
		exit(1);
	}
	ft_initstruct(data);
	if (data->file2 < 0)
	{
		perror("Error file2 : ");
		exit(1);
	}
}

static void	ft_init(t_bdata *data)
{
	if (data->argc < 5)
		ft_exit("Error : more earguments expected ! !", 1);
	if (ft_strcmp("here_doc", data->argv[1]))
	{
		if (data->argc < 6)
			ft_exit("Error : more earguments expected ! !", 1);
		data->lim = ft_strjoin(data->argv[2], "\n");
		data->file2 = open(data->argv[data->argc - 1], \
		O_WRONLY | O_CREAT | O_APPEND, 0755);
		data->file1 = data->file2;
	}
	else
	{
		data->file1 = open(data->argv[1], O_RDONLY);
		data->file2 = open(data->argv[data->argc - 1], \
		O_WRONLY | O_CREAT | O_TRUNC, 0755);
	}
	ft_init_suit(data);
	errno = 0;
}

static void	ft_tidyup(t_bdata *data)
{
	int	i;
	int	pid;

	i = 0;
	pid = 0;
	ft_close_fd(data);
	while (wait(NULL) > 0)
		pid++;
	free(data->lim);
	data->lim = NULL;
	while (i < data->n)
	{
		ft_free_split(&(data->cmdn[i]));
		i++;
	}
	close(data->file1);
	close(data->file2);
}

int	main(int argc, char **argv, char **envp)
{
	t_bdata	data;
	int		i;

	i = 1;
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	data.lim = NULL;
	ft_init(&data);
	if (data.lim)
		proc0(&data);
	else
		proc1(&data);
	while (i < data.n - 1)
		proci(&data, i++);
	procn(&data, i);
	ft_tidyup(&data);
	return (0);
}
