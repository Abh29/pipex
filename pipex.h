#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <stdint.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_dpipe
{
	int		va[2];
	int		vien[2];
}				t_dpipe;

typedef struct s_cmdl
{
	char	cmds[100][2];
}				t_cmdl;

void	ft_exit(char *str, int status);
void	ft_exit_errno(char *str, int status);
void	ft_free_split(char **split);
char	*ft_getPATH(char **envp);
char	*ft_which(char	*cmd, char **envp);
char	**ft_split_cmd(char *cmd, char **envp);

#endif
