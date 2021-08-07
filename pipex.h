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

# define MAX_PIPE 128

typedef struct s_dpipe
{
	int		va[2];
	int		vien[2];
}				t_dpipe;

typedef struct s_data
{
    int		p[2];
    int		argc;
    char	**argv;
    char	**envp;
	char	**cmd1;
	char	**cmd2;
    int		file1;
    int		file2;
    int		pid1;
    int		pid2;
}				t_data;

typedef struct s_bdata
{
	int		pn[MAX_PIPE][2];
	char	**cmdn[MAX_PIPE];
    int		argc;
    char	**argv;
    char	**envp;
	char	*lim;
    int		file1;
    int		file2;
	int		n;
}				t_bdata;

void	ft_exit(char *str, int status);
void	ft_exit_errno(char *str, int status);
void	ft_free_split(char ***split);
char	*ft_getPATH(char **envp);
char	*ft_which(char	*cmd, char **envp);
char	**ft_split_cmd(char *cmd, char **envp);
int		ft_strcmp(char *s1, char *s2);
void	ft_close_fd(t_bdata *data);
void	proc0(t_bdata *data);
void	proc1(t_bdata *data);
void	proci(t_bdata *data, int i);
void	procn(t_bdata *data, int n);


#endif
