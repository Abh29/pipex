/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehill <mehill@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:52:33 by mehill            #+#    #+#             */
/*   Updated: 2021/10/13 20:52:34 by mehill           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_exit(char *str, int status)
{
	ft_putendl_fd(str, STDERR_FILENO);
	exit(status);
}

void	ft_exit_errno(char *str, int status)
{
	errno = status;
	perror(str);
}
