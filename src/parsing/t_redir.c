#include "minishell.h"
int get_mode(int type)
{
    if(type == REDIR_IN)
        return O_RDONLY;
    if(type == REDIR_OUT)
        return O_RDWR |O_TRUNC| O_CREAT;
    if(type == APPEND)
        return O_APPEND| O_RDWR | O_CREAT;
    return -1;
}
int get_perm(int type)
{
    if(type == REDIR_IN)
        return 0;
    if(type == REDIR_OUT)
        return 0644;
    if(type == APPEND)
        return 0644;
    return -1;
}
int get_dup(int type)
{
    if(type == REDIR_IN)
        return STDIN_FILENO;
    if(type == REDIR_OUT)
        return STDOUT_FILENO;
    if(type == APPEND)
        return STDOUT_FILENO;
    return -1;
}
t_rdr *ft_redirnew(char *value,int type)
{
   t_rdr *new;
  new = _malloc((sizeof(t_rdr)));
  if(!new)
      return NULL;
  new->value = ft_strdup(value);
  new->next = NULL;
  new->fd = -1;
  new->type = type;
  new->mode = get_mode(type);
  new->dup = get_dup(type);
  new->perm = get_perm(type);
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