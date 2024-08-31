/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .execution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 09:51:34 by ahanaf            #+#    #+#             */
/*   Updated: 2024/08/21 16:06:10 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

<<<<<<< HEAD
=======
//TODO $$
int get_pid()
{
    int pid;

    pid = fork();
    if (!pid)
        exit(0);
    return (pid - 2);
}
void update_status(int new_status)
{
    change_env(get_ms()->env_ld,"?",ft_itoa(new_status));
}
>>>>>>> afe0304d9f6d9cc222c39c279787f25a92c796b6

void handle_rdr(t_rdr *redir,int flag)
{
    int file;
    //char *here_doc_name = NULL;
    //dprintf(2,"hello %s\n",redir->type);
    while(redir)
    {
        if(redir->type == REDIR_IN)
        {
            file = open(redir->value,O_RDONLY);
            if(file == -1)
            {
               perror(redir->value);
               if(flag)
                    exit(1);
                return ;
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
               if(flag)
                    exit(1);
                return ;
            };
            dup2(file,STDOUT_FILENO);
            close(file);
        }
        if(redir->type == APPEND)
        {
            file = open(redir->value,O_APPEND| O_RDWR | O_CREAT,0644);
            if(file == -1)
            {
               perror(redir->value);
               if(flag)
                    exit(1);
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
        __exit(ft_atoi(get_env(get_ms()->env_ld,"?")));
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
    execve(path,nargs,env);
    //TODO handle failed execve
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
void exec_child2(t_cmd *cmd,int in_fd,int out_fd[2])
{

    if(in_fd != STDIN_FILENO)
        {
            dup2(in_fd,STDIN_FILENO);
            close(in_fd);
        };
    if(out_fd[1] != STDOUT_FILENO)
        {
            dup2(out_fd[1],STDOUT_FILENO);
            close(out_fd[1]);
        }
    if(out_fd[0] != 0)
        close(out_fd[0]);
    handle_rdr(cmd->redir,1);
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
// void read_heredoc(t_rdr *hrdoc)
// {
//     char *line;
//     char *str = NULL;
//     while(TRUE)
//     {
//         line = readline(">");
//         if(!line || !ft_strcmp(hrdoc->value, line))
//             break;
//         str = ft_strjoin(str, line);
//     }
//     printf("-------------------------str---------------------------\n");
//     printf("%s",str);
// }

// void check_heredoc(t_cmd *cmd)
// {
//     t_rdr *temp_rdr;
//     while(cmd)
//     {
//         temp_rdr =cmd->heredoc;
//         while(temp_rdr)
//         {
//             read_heredoc(temp_rdr);
//             temp_rdr = temp_rdr->next;
//         }
//         cmd = cmd->next;
//     }
// }
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
            _exit(ft_atoi(get_env(get_ms()->env_ld,"?")));
        }
        else if(!ft_strcmp((char *)cmd->args->content,"export"))
            _export(get_ms()->env_ld,cmd->args->next);
        dup2(std_in,STDIN_FILENO);
        dup2(std_out,STDOUT_FILENO);
        close(std_in);
        close(std_out);
        return 1;
    }
    // close(std_in);
    // close(std_out);
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
    // if(WIFSIGNALED(status))
    //     return WTERMSIG(status) + 128;
    return 0;
}
void execute_cmds(t_cmd *cmd)
{
    int i;
    int nbr;
    nbr = cmd_nbr(cmd);
    i = 0;
    pid_t *pids = (int *)ft_allocator(sizeof(pid_t) * (cmd_nbr(cmd)),"execution");
    int pipefd[2];
    pipefd[READ] = 0;
    int tmp;
    tmp = STDIN_FILENO;
    pipefd[WRITE] = STDOUT_FILENO;
    if(!cmd->next)
        update_underscore(cmd);
    if(!cmd->next && check_single_builtin(cmd))
        return;
    while(cmd)
    {
        if(cmd->next)
            pipe(pipefd);
        pids[i] = fork();
        if(pids[i] == CHILD)
            exec_child2(cmd,tmp,pipefd);
        else
        {
            if(pipefd[WRITE] != 1)
                close(pipefd[WRITE]);
            if(tmp != 0)
                close(tmp);
            tmp = pipefd[READ];
        }
        i++;
        cmd = cmd->next;
    }
    if(tmp != 0)
        close(tmp);
    int status;
    i = 0;
	while (i < nbr)
		waitpid(pids[i++], &status, 0);
    update_status(get_status(status));
    // print_export(*g_minishell.env_ld);
}
