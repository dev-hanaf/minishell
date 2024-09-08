/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 09:51:34 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/07 03:21:09by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "minishell.h"


void update_status(int new_status)
{
    get_ms()->status = new_status;
    // get_env_ld(get_ms()->env_ld,"?")->value = ft_itoa(new_status);
}
int ft_close(int fd)
{
    if(fd != 0 && fd != 1)
        return close(fd);
    return -1;
}
int check_ambiguous(t_rdr *redir,int *file,char **str,int flag)
{
	char **strs;
	strs = expand(*get_ms()->env_ld,redir->value);
	if(ft_strlen_2d_array(strs) > 1 || !strs[0])
	{
		ft_putstr_fd("minishell: ",2);
		ft_putstr_fd(redir->value,2);
		ft_putstr_fd(": ambiguous redirect\n",2);
		if(flag)
			clean_exit(1);
        get_ms()->execute = 1;
		return 1;
	}
	*file = open(strs[0],redir->mode,redir->perm);
	*str = strs[0];
	return 0;
}
void handle_rdr(t_rdr *redir,int flag)
{
    int file;
	char *str;
	//TODO handle expand here
    while(redir)
    {
        if(redir->type == REDIR_IN || redir->type == REDIR_OUT || redir->type == APPEND)
        {
			check_ambiguous(redir,&file,&str,flag);
            if(file == -1)
            {
			   ft_putstr_fd("minishell: ",2);
               perror(str);
               get_ms()->execute = 1;
               if(flag)
                    clean_exit(1);
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

int check_builtin(char **args,int *status)
{
    //TODO khdm liya hado unset bohdha li khdama
    //printf(GREEN"%s\n"NC, args[0]);
    if(!args || !*args)
        return 0;
    if(!ft_strcmp(args[0],"export"))
    {
        _export(get_ms()->env_ld,++args);
        return 1;
    }
    else if(!ft_strcmp(args[0],"echo"))
    {
        _echo(++args);
		*status = 0;
        return 1;
    }
    else if(!ft_strcmp(args[0],"pwd"))
    {
        _pwd();
		*status = 0;
        return 1;
    }
    else if(!ft_strcmp(args[0],"exit"))
    {
        __exit(++args);
		//TODO handle it mate zmourid
        return 1;
    }
    else if(!ft_strcmp(args[0],"env"))
    {
        printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n\n\n");
        _env(*get_ms()->env_ld);
		*status = 0;
        return 1;
    }
	else if(!ft_strcmp(args[0],"unset"))
	{
		*status = _unset(get_ms()->env_ld,++args);
		return 1;
	}
	return 0;
}
void exec_cmd(t_list *args)
{
    int status;
    status = 0;
    if(!args)
        clean_exit(0);
    char **nargs = ld_to_arr_and_expand(args);
    if(!nargs)
        clean_exit(0);
    if(check_builtin(nargs,&status))
        clean_exit(status);
    char **env = env_to_arr(*get_ms()->env_ld);
    char *path = get_cmd_path(nargs[0],env);
    execve(path,nargs,env);
    _free();
    _free_env();
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
	//todo handle exit
    char **strs = ld_to_arr_and_expand(cmd->args);
    if(!strs || !*strs)
        return 0;
    if(is_built_in(strs[0]))
    {
        int std_in = dup(STDIN_FILENO);
        int std_out = dup(STDOUT_FILENO);
        handle_rdr(cmd->redir,0);
        if(get_ms()->execute)
            return 1;
        if(!ft_strcmp(strs[0],"echo"))
        {
            _echo(ld_to_arr_and_expand(cmd->args->next));
            update_status(0);
        }
        else if(!ft_strcmp((char *)cmd->args->content,"cd"))
        {
            if(cmd->args->next)
                update_status(_cd(ld_to_arr_and_expand(cmd->args->next),get_ms()->env_ld));
            else
                update_status(_cd(NULL,get_ms()->env_ld));
        }
        else if(!ft_strcmp((char *)cmd->args->content,"pwd"))
            _pwd();
        else if(!ft_strcmp((char *)cmd->args->content,"env"))
            _env(*get_ms()->env_ld);
        else if(!ft_strcmp(strs[0],"exit"))
        {
            close(std_in);
            close(std_out);
            __exit(ld_to_arr_and_expand(cmd->args->next));
        }
        else if(!ft_strcmp(strs[0],"export"))
            _export(get_ms()->env_ld,++strs);
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
    t_env *underscore;
    underscore = NULL;
    while(cmd->next)
        cmd = cmd->next;
    arg = cmd->args;
	if(!arg)
		return;
    while(arg && arg->next)
	{
        arg = arg->next;
	}
	char **strs = expand(*get_ms()->env_ld,(char *)arg->content);
    if(!strs || !*strs)
        return ;
    underscore = get_env_ld(get_ms()->env_ld," ");
    if(!underscore)
    {
        add_to_back_env(get_ms()->env_ld,new_env("_",strs[ft_strlen_2d_array(strs) - 1]));
        return ;
    }
    get_env_ld(get_ms()->env_ld,"_")->value = strs[ft_strlen_2d_array(strs) - 1];
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
    //if(!cmd->next)
    //    update_underscore(cmd);
    if(!cmd->next && check_single_builtin(cmd))
        return NULL;
    exec = _malloc(sizeof(t_exec));
    exec->pids = (pid_t *)_malloc(sizeof(pid_t) * (cmd_nbr(cmd)));
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
