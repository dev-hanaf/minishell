#include "minishell.h"

void sigHandler_hrdc(int sig)
{
    write(1,"\n",1);
	clean_exit(sig + 128);
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

void	sigHerdoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		clean_exit(130);
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", 2);
		clean_exit(131);
	}
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
		signal(SIGINT,SIG_IGN);
		signal(SIGQUIT,SIG_IGN);
		waitpid(pid,status,0);
		return *status;//	struct sigaction sa; //	sa.sa_flags = -1;
	}
	signal(SIGINT,sigHerdoc);
	signal(SIGQUIT,SIG_IGN);
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
		clean_exit(0);
        return 0;
	}
	if(!isExpand)
		str = expand_herdoc(*get_ms()->env_ld, str);
    if(!write(pipefd[WRITE],str,ft_strlen(str)))
	{
			dprintf(2,"error writing to pipe\n");
			return 0;
	}
    close_heredoc(get_ms()->cmd);
    close(pipefd[WRITE]);
	close(pipefd[READ]);
	clean_exit(0);
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
