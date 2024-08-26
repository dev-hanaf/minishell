#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
//todo parse the line and execute the command
t_rdr *ft_redirnew(char *value,int type)
{
   t_rdr *new;
  new = ft_allocator((sizeof(t_rdr)),"parsing");
  if(!new)
      return NULL;
  new->value = ft_strdup(value);
  new->next = NULL;
  new->fd = -1;
  new->type = type;
  return  new;
}
char *ft_strjoin_char(char *s1,char c)
{
    char *new = ft_allocator((sizeof(char)* ft_strlen(s1) + 2),"parsing");
    if(!new)
        return ft_strdup("");
    int i = 0;
    while(s1[i])
    {
        new[i] = s1[i];
        i++;
    }
    new[i++] = c;
    new[i] = 0;
    return new;
}
char *ft_readline(char *txt)
{
    char *line;
    char buff;
    char *test = ft_strjoin_char("aloh", 'a');
    dprintf(2,"str = %s\n",test);
    write(1,txt,ft_strlen(txt));
    while(TRUE)
    {
        if(read(0,&buff,1) == 0)
            break;
        dprintf(2, "buff = %c\n", buff);
        line = ft_strjoin_char(line,buff);
        if(buff == '\n' || !buff || buff == 'q')
            break;
    }
    return line;
}

char	*ft_strjoin_ln(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if(!s1 && s2)
	   return ft_strdup(s2);
	if(!s2 && s1)
	   return ft_strdup(s2);
	if (s2 == NULL)
	{
		s2 = ft_allocator(sizeof(char), "s2");
		if (!s2)
			return (NULL);
		s2[0] = '\0';
	}
	str = ft_allocator((ft_strlen(s1) + ft_strlen(s2) + 1 + 1), "join");
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i++] = '\n';
	str[i] = 0;
	return (str);
}
int is_stillhrdc(t_rdr *tmp)
{
    while(tmp)
    {
        if(tmp->type == HERDOC)
            return 1; 
    }
    return 0;
}

void open_heredoc(t_rdr *heredocs)
{
    char prompt[] = ">";
    char *str = NULL;
    char *line = NULL;
    t_rdr *last_heredoc;
    last_heredoc = NULL;
    while(heredocs)
    {
        if(heredocs->type != HERDOC)
        {
            heredocs = heredocs->next;
            continue;
        }
        while(TRUE)
        {
            line = readline(prompt);
            dprintf(2, "heredoc eof = %s\n",heredocs->value);
            if(!ft_strcmp(line, heredocs->value))
                break;
            if(!heredocs->next)
            {
                last_heredoc = heredocs;
                str = ft_strjoin(str, line);
                str =ft_strjoin(str, "\n");
            }
        }
        heredocs = heredocs->next;
    }
    if(!str)
        return;
    int pipefd[2];
    str = expand(*g_minishell.env_ld,str);
    pipe(pipefd);
    //printf("str =%s",str);
    //file = open(name, O_RDWR |O_TRUNC| O_CREAT,0644);
    write(pipefd[WRITE],str,ft_strlen(str));
    close(pipefd[WRITE]);
    last_heredoc->fd = pipefd[READ];
   //unlink("ofile");
}
void handle_heredoc(t_cmd *cmd)
{
    while(cmd)
    {
      open_heredoc(cmd->redir);
      cmd = cmd->next;
    }
}
void ft_rdraddback(t_rdr **rdr,t_rdr *new)
{
    if(!rdr)
        return ;
    if(!*rdr)
    {
        *rdr = new;
        return ;
    }
    t_rdr *temp = *rdr;
    while(temp->next)
        temp = temp->next;
    temp->next = new;
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
            add_to_back_cmd(&cmd, new_cmd());
            curr_cmd = get_last_cmd(cmd);
            tokens = tokens->next;
            continue;
        }
        if((tokens->type == REDIR_IN || tokens->type == REDIR_OUT || tokens->type == HERDOC || tokens->type == APPEND) && tokens->next)
        {
           tmp_rdr = ft_redirnew(tokens->next->value, tokens->type);
            ft_rdraddback(&curr_cmd->redir, tmp_rdr);
            tokens = tokens->next->next;
            continue;
        }
        ft_lstadd_back(&curr_cmd->args, ft_lstnew(tokens->value));
        tokens = tokens->next;
    }
    //print_cmds(cmd);
    handle_heredoc(cmd);
    return cmd;
}