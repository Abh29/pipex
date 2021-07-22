#include "../pipex.h"

void    ft_free_split(char **split)
{
    if (split == NULL)
        return ;
    while (*split != NULL)
    {
        free(*split);
        *split = NULL;
        split++;
    }
    //p = NULL;
    //free(*split);
    //*split = NULL;
}