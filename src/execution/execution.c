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

#include "minishell.h"

void handle_redirections(t_cmd *cmd)
{
    int outfile;
    int infile = -1;
    if(cmd->redir_out)
    {
        while(cmd->redir_out && cmd->redir_out->next)
        {
            outfile = open((char *)cmd->redir_out->content,O_RDWR| O_CREAT,0644);
            close(outfile);
            cmd->redir_out = cmd->redir_out->next;
        }
        outfile = open((char *)cmd->redir_out->content,O_RDWR| O_CREAT,0644);
        dup2(outfile,STDOUT_FILENO);
        close(outfile);
        dprintf(2,"------------outfile == %s--------------\n",(char *)cmd->redir_out->content);
    }
    if(cmd->redir_in)
    {
        while(cmd->redir_in && cmd->redir_in->next)
        {
            infile = open((char *)cmd->redir_in->content,O_RDONLY);
            close(infile);
            cmd->redir_in = cmd->redir_in->next;
        }
        infile = open((char *)cmd->redir_in->content,O_RDONLY);
        dprintf(2, "fd =%d\n",infile);
        dup2(infile,STDIN_FILENO);
        dprintf(2,"------------ in == %s %d--------------\n",(char *)cmd->redir_in->content,infile);
        close(infile);
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
    handle_redirections(cmd);
    exec_cmd(cmd->args);
}

void execute_cmds(t_cmd *cmd)
{
    int i;
    i = 0;
    //printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$-----------%d---------$$$$$$$$$$$$$$$$$$$$$\n",getpid());
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