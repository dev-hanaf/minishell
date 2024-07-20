#include "libft.h"
#include "minishell.h"
#include <stdio.h>
//todo parse the line and execute the command
t_rdr *ft_redirnew(char *value,int type)
{
   t_rdr *new;
  new = malloc((sizeof(t_rdr)));
  if(!new)
      return NULL;
  new->value = ft_strdup(value);
  new->next = NULL;
  new->type = type;
  return  new;
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
            ft_rdraddback(&curr_cmd->redir, ft_redirnew(tokens->next->value,tokens->type));
            tokens = tokens->next->next;
            continue;
        }
        ft_lstadd_back(&curr_cmd->args, ft_lstnew(tokens->value));
        tokens = tokens->next;
    }
    return cmd;
}