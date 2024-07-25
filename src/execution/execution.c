/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .execution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 09:51:34 by ahanaf            #+#    #+#             */
/*   Updated: 2024/05/19 09:52:04 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

void handle_rdr(t_rdr *redir)
{
    int file;
    //char *here_doc_name = NULL;
    
    while(redir)
    {
        if(redir->type == REDIR_IN)
        {
            file = open(redir->value,O_RDONLY);
            if(file == -1)
            {
               perror("khoya  nta rak  mrid");
               exit(0);
            };
            dup2(file,STDIN_FILENO);
            close(file);
        }
        if(redir->type == REDIR_OUT)
        {
            file = open(redir->value, O_RDWR |O_TRUNC| O_CREAT,0644);
            if(file == -1)
            {
               perror(redir->value);
               exit(0);
            };
            dup2(file,STDOUT_FILENO);
            close(file);
        }
        if(redir->type == APPEND)
        {
            file = open(redir->value,O_APPEND| O_RDWR | O_CREAT,0644);
            if(file == -1)
            {
               perror("khoya  nta rak  mrid");
               exit(0);
            };
            dup2(file,STDOUT_FILENO);
            close(file);
        }
        if(redir->type == HERDOC)
            {
                if(redir->fd != -1)
                {
                    dup2(redir->fd,STDIN_FILENO);
                    close(redir->fd);
                };
            }
        redir = redir->next;
    }
}

void exec_cmd(t_list *args)
{
    char **nargs = ld_to_arr(args);
    char **env = g_minishell.env;
    char *path = get_cmd_path(nargs[0],env);
    execve(path,nargs,env);
}
void exec_child(t_cmd *cmd,int in_fd,int out_fd)
{
    
    if(in_fd != STDIN_FILENO)
        {
            dup2(in_fd,STDIN_FILENO);
            close(in_fd);
        };
    if(out_fd != STDOUT_FILENO)
        {
            dup2(out_fd,STDOUT_FILENO);
            close(out_fd);
        }
    ///handle_rdr(cmd->redir);
    exec_cmd(cmd->args);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while ((str1[i] == str2[i]) && str1[i] && str2[i])
	{
		i++;
	}
	return (str1[i] - str2[i]);
}
void read_heredoc(t_rdr *hrdoc)
{
    char *line;
    char *str = NULL;
    while(TRUE)
    {
        line = readline(">");
        if(!line || !ft_strcmp(hrdoc->value, line))
            break;
        str = ft_strjoin(str, line);
    }
    printf("-------------------------str---------------------------\n");
    printf("%s",str);
}

void check_heredoc(t_cmd *cmd)
{
    t_rdr *temp_rdr;
    while(cmd)
    {
        temp_rdr =cmd->heredoc;
        while(temp_rdr)
        {
            read_heredoc(temp_rdr);
            temp_rdr = temp_rdr->next;
        }
        cmd = cmd->next;
    }
}
void execute_cmds(t_cmd *cmd)
{
    int i;
    i = 0;
    pid_t *pids = (int *)malloc(sizeof(pid_t) * (cmd_nbr(cmd)));
    int pipefd[2];
    int tmp;
    tmp = STDIN_FILENO;
    pipefd[WRITE] = STDOUT_FILENO;
    while(cmd)
    {
        if(cmd->next)
            pipe(pipefd);
        pids[i] = fork();
        if(pids[i] == CHILD)
            exec_child(cmd,tmp,pipefd[WRITE]);
        else
        {
            if(pipefd[WRITE] != 1)
                close(pipefd[WRITE]);
            if(!cmd->next)
                pipefd[WRITE] = STDOUT_FILENO;
            if(tmp != 0)
                close(tmp);
            tmp = pipefd[READ];
        }
        i++;
        cmd = cmd->next;
    }
    if(tmp != 0)
        close(tmp);
    i++;
    while(i--)
        wait(NULL);
}