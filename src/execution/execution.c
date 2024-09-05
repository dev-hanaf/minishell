/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 09:51:34 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/31 16:26:22 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

void update_status(int new_status)
{
    get_ms()->status = new_status;
    get_env_ld(get_ms()->env_ld,"?")->value = ft_itoa(new_status);
}
int ft_close(int fd)
{
    if(fd != 0 && fd != 1)
        return close(fd);
    return -1;
}

void handle_rdr(t_rdr *redir,int flag)
{
    int file;
    while(redir)
    {
        if(redir->type == REDIR_IN || redir->type == REDIR_OUT || redir->type == APPEND)
        {
            file = open(redir->value,redir->mode,redir->perm);
            if(file == -1)
            {
               perror(redir->value);
               if(flag)
                    exit(1);
                return ;
            };
            dup2(file,redir->dup);
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

int check_builtin(t_list *args,int *status)
{
    if(!ft_strcmp((char *)args->content,"export"))
    {
        *status = _export(get_ms()->env_ld,args->next);
        return 1;
    }
    else if(!ft_strcmp((char *)args->content,"echo"))
    {
        _echo(ld_to_arr(args->next));
        return 1;
    }
    else if(!ft_strcmp((char *)args->content,"pwd"))
    {
        _pwd();
        return 1;
    }
    else if(!ft_strcmp((char *)args->content,"exit"))
    {
        __exit(get_ms()->status);
        return 1;
    }
    else if(!ft_strcmp((char *)args->content,"env"))
    {
        _env(*get_ms()->env_ld);
        return 1;
    }
    return 0;
}
void exec_cmd(t_list *args)
{
    int status;
    status = 0;
    if(!args)
        exit(0);
    if(check_builtin(args,&status))
        exit(status);
    char **nargs = ld_to_arr(args);
    char **env = env_to_arr(*get_ms()->env_ld);
    char *path = get_cmd_path(nargs[0],env);
    execve("",nargs,env);
    //TODO handle failed execve
}
void exec_child(t_cmd *cmd,int in_fd,int out_fd[2])
{
    handle_child_signals();
    dup2(in_fd,STDIN_FILENO);
    ft_close(in_fd);
    dup2(out_fd[WRITE],STDOUT_FILENO);
    ft_close(out_fd[WRITE]);
    ft_close(out_fd[READ]);
    handle_rdr(cmd->redir,1);
    exec_cmd(cmd->args);
}

int is_built_in(char *command)
{
    if(!ft_strcmp(command,"echo"))
        return 1;
    if(!ft_strcmp(command,"cd"))
        return 1;
    if(!ft_strcmp(command,"exit"))
        return 1;
    if(!ft_strcmp(command,"pwd"))
        return 1;
    if(!ft_strcmp(command,"export"))
        return 1;
    if(!ft_strcmp(command,"env"))
        return 1;
    return 0;
}

int check_single_builtin(t_cmd *cmd)
{
    if(cmd->args && is_built_in(cmd->args->content))
    {
        int std_in = dup(STDIN_FILENO);
        int std_out = dup(STDOUT_FILENO);
        handle_rdr(cmd->redir,0);
        if(!ft_strcmp((char *)cmd->args->content,"echo"))
            _echo(ld_to_arr(cmd->args->next));
        else if(!ft_strcmp((char *)cmd->args->content,"cd"))
        {
            if(cmd->args->next)
                _cd(cmd->args->next->content,get_ms()->env_ld);
            else
                _cd(NULL,get_ms()->env_ld);
        }
        else if(!ft_strcmp((char *)cmd->args->content,"pwd"))
            _pwd();
        else if(!ft_strcmp((char *)cmd->args->content,"env"))
            _env(*get_ms()->env_ld);
        else if(!ft_strcmp((char *)cmd->args->content,"exit"))
        {
            close(std_in);
            close(std_out);
            _exit(get_ms()->status);
        }
        else if(!ft_strcmp((char *)cmd->args->content,"export"))
            get_ms()->status = _export(get_ms()->env_ld,cmd->args->next);
        dup2(std_in,STDIN_FILENO);
        dup2(std_out,STDOUT_FILENO);
        close(std_in);
        close(std_out);
        return 1;
    }
    return 0;
}
void update_underscore(t_cmd *cmd)
{
    t_list *arg;
    while(cmd->next)
        cmd = cmd->next;
    arg = cmd->args;
	if(!arg)
		return;
    while(arg && arg->next)
        arg = arg->next;
    get_env_ld(get_ms()->env_ld,"_")->value = ft_strdup(arg->content);
}
int get_status(int status)
{
    if(WIFEXITED(status))
        return WEXITSTATUS(status);
    if(WIFSIGNALED(status))
        return WTERMSIG(status) + 128;
    return 0;
}
t_exec *init_exec(t_cmd *cmd)
{
    t_exec *exec;
    if(!cmd)
        return NULL;
    if(!cmd->next)
        update_underscore(cmd);
    if(!cmd->next && check_single_builtin(cmd))
        return NULL;
    exec = ft_allocator(sizeof(t_exec),"execution");
    exec->pids = (pid_t *)ft_allocator(sizeof(pid_t) * (cmd_nbr(cmd)),"execution");
    exec->pipefd[READ] = 0;
    exec->pipefd[WRITE] = 1;
    exec->tmp = STDIN_FILENO;
    exec->i = 0;
    return exec;
}
void execute_cmds(t_cmd *cmd,int nbr)
{
    t_exec *exec;
    int i = 0;
    int status;
    exec = init_exec(cmd);
    if(exec == NULL)
        return;
    while(cmd)
    {
        if(cmd->next)
            pipe(exec->pipefd);
        exec->pids[i] = fork();
        if(exec->pids[i] == CHILD)
            exec_child(cmd,exec->tmp,exec->pipefd);
        else
        {
            handle_parent_signals();
            ft_close(exec->pipefd[WRITE]);
            ft_close(exec->tmp);
            exec->tmp = exec->pipefd[READ];
        }
        i++;
        cmd = cmd->next;
    }
    ft_close(exec->tmp);
    i = 0;
	while (i < nbr)
		waitpid(exec->pids[i++], &status, 0);
    update_status(get_status(status));
}
