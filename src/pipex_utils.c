#include "../pipex.h"


void    ft_free_split(char ***split)
{
	void *p = *split;

    if (split == NULL || *split == NULL)
        return ;
    while (**split != NULL)
    {
        free(**split);
        **split = NULL;
        (*split)++;
    }
	*split = NULL;
	free(p);
	p = NULL;
}