#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
//todo parse the line and execute the command

void sigHandler_hrdc(int sig)
{
    write(1,"\n",1);
	exit(sig + 128);
}
t_rdr *get_last_hrdc(t_rdr *redir)
{
	t_rdr *last;
	last = NULL;
	if(!redir)
		return NULL;
	while(redir)
	{
		if(redir->type == HERDOC)
			last = redir;
		redir = redir->next;
	}
	return  last;
}
char *handle_quotes_v2(char *eof,int *expand)
{
	if(ft_strchr(eof, '\'') || ft_strchr(eof, '\"'))
		*expand = 1;
	return handle_quotes(eof);
}
int open_heredoc(t_rdr *heredocs,int *pipefd, int *status)
{
    char *str = NULL;
    char *line = NULL;
    int isExpand = 0; //TODO check if we need to expand
	int pid;
	pid = fork();
    char *eof;
	if(pid != CHILD)
	{
        handle_parent_signals();
		waitpid(pid,status,0);
		return *status;//	struct sigaction sa; //	sa.sa_flags = -1;
	}
	signal(SIGINT,SIG_DFL);
    while(heredocs)
    {
        if(heredocs->type != HERDOC)
        {
            heredocs = get_last_hrdc(heredocs);
            continue;
        }
        eof = handle_quotes_v2(heredocs->value,&isExpand);
        while(TRUE)
        {
            line = readline(">");
            if( line == NULL || !ft_strcmp(line, eof))
                break;
            if(get_last_hrdc(heredocs) == heredocs)
            {
                str = ft_strjoin(str, line);
                str = ft_strjoin(str, "\n");
            }
        }
        heredocs = heredocs->next;
    }
    if(!str)
	{
		close(pipefd[WRITE]);
		close(pipefd[READ]);
		exit(0);
        return 0;
	}
//	if(!isExpand)
//		str = expand(*get_ms()->env_ld, str);
    if(!write(pipefd[WRITE],str,ft_strlen(str)))
	{
			dprintf(2,"error writing to pipe\n");
			return 0;
	}
    close_heredoc(get_ms()->cmd);
    close(pipefd[WRITE]);
	close(pipefd[READ]);
	exit(0);
	return 1;
}

int  handle_heredoc(t_cmd *cmd)
{
    int pipefd[2];
	int status;
	t_rdr *last;
    while(cmd)
    {
		last = get_last_hrdc(cmd->redir);
		if(last)
		{
            pipe(pipefd);
			open_heredoc(cmd->redir,pipefd,&status);
			close(pipefd[WRITE]);
			if(status != 0)
			{
                close(pipefd[READ]);
				get_ms()->status = status;
				update_status(get_status(status));
				return status;
			}
			last->fd = pipefd[READ];
		}
      cmd = cmd->next;
    }
	return 0;
}

t_cmd *parse_cmds(t_tokenizer *tokens)
{
    t_cmd *cmd = new_cmd();
    t_cmd *curr_cmd = cmd;
    t_rdr *tmp_rdr;
    tmp_rdr = NULL;
    while(tokens)
    {
        if(tokens->type == PIPE)
        {
            curr_cmd = new_cmd();
            add_to_back_cmd(&cmd, curr_cmd);
            tokens = tokens->next;
            continue;
        }
        if((tokens->type == REDIR_IN || tokens->type == REDIR_OUT || tokens->type == HERDOC || tokens->type == APPEND))
        {
           tmp_rdr = ft_redirnew(tokens->next->value, tokens->type);
            ft_rdraddback(&curr_cmd->redir, tmp_rdr);
            tokens = tokens->next->next;
            continue;
        }
        //if(tokens->value)//TODO this should be handled in parsing
         ft_lstadd_back(&curr_cmd->args, ft_lstnew(tokens->value));
        tokens = tokens->next;
    }
    get_ms()->cmd = cmd;
    if(handle_heredoc(cmd))
		return NULL;
    return cmd;
}
