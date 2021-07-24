#include "../pipex.h"

char	*ft_getPATH(char **envp)
{
	char	*start;
	int		i;

	if (!envp || !(*envp))
		return (NULL);
	start = "PATH=";
	i = 0;
	while (envp[i])
	{
		if(ft_strnstr(envp[i], start, 5))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

static char	*ft_check_possible(char	**paths, char *scmd)
{
	char	*pcmd;

	pcmd = NULL;
	while (*paths)
	{
		pcmd = ft_strjoin(*(paths++), scmd);
		if (access(pcmd, F_OK | X_OK) == 0)
			break;
		free(pcmd);
		pcmd = NULL;
	}
	return (pcmd);
}

char	*ft_which(char	*cmd, char **envp)
{
	char	**paths;
	char	*scmd;
	char	*pcmd;

	if (!cmd || !envp || !(*envp))
		return (NULL);
	scmd = ft_strjoin("/", cmd);
	paths = ft_split(ft_getPATH(envp) + 5, ':');
	pcmd = ft_check_possible(paths, scmd);
	ft_free_split(&paths);
	free(scmd);
	scmd = NULL;
	if (pcmd == NULL)
		return (ft_strdup(cmd));
	return (pcmd);
}

char	**ft_split_cmd(char *cmd, char **envp)
{
	char	**out;
	char	*pcmd;

	if (cmd == NULL)
		return (NULL);
	out = ft_split(cmd, ' ');
	pcmd = ft_which(out[0], envp);
	if (pcmd)
	{
		free(out[0]);
		out[0] = pcmd;
	}
	return (out);
}
