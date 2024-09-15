/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syscalls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:49:14 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/15 00:35:10 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_close(int fd)
{
	if (fd != 0 && fd != 1 && fd != -1)
		return (close(fd));
	return (-1);
}

ssize_t	ft_write(int fd, const void *buf, size_t count)
{
	ssize_t	len;

	len = write(fd, buf, count);
	if (len == -1)
	{
		perror("write");
		clean_exit(1);
	}
	return (len);
}

int	ft_dup2(int oldfd, int newfd)
{
	int	fd;

	fd = 0;
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup");
		clean_exit(1);
	}
	return (fd);
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		clean_exit(1);
	}
	return (pid);
}

int	*ft_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		clean_exit(1);
	}
	return (pipefd);
}
