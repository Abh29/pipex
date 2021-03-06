/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:52:50 by mehill            #+#    #+#             */
/*   Updated: 2021/10/13 20:52:51 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_free_split(char ***split)
{
	void	*p;

	p = (char **)*split;
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

int	ft_strcmp(char *s1, char *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (1);
	return (0);
}

void	ft_close_fd(t_bdata *data)
{
	int	i;

	if (data == NULL)
		return ;
	i = 0;
	while (i < data->n)
	{
		close(data->pn[i][0]);
		close(data->pn[i][1]);
		i++;
	}
}
