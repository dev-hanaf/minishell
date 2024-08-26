#include "minishell.h"

int is_last(t_rdr *redir)
{
    if(!redir)
        return -1;
    int type = redir->type;
    redir = redir->next;
    while(redir)
    {
        if(redir->type == type)
            return 0;
        redir = redir->next;
    }
    return 1;
}
void print_rdr(t_rdr *redir)
{
    while(redir)
    {
        if(redir->type == REDIR_IN)
            dprintf(2,"redir in %s\n",redir->value);
        if(redir->type == REDIR_OUT)
            dprintf(2,"redir out %s\n",redir->value);
        if(is_last(redir))
            dprintf(2,"redir is the last %s\n",redir->value);
        redir = redir->next;
    }
}

void print_args(t_list *arg,char *name)
{
    if(!arg)
        return;
    printf("%s:",name);
    while (arg) {
        printf("%s", (char *)arg->content);
        if(arg->next)
            printf(",");
        arg = arg->next;
    }
    printf("\n");
}

void print_redir(t_rdr *arg)
{
    if(!arg)
        return;
    printf("redirections:");
    while (arg) {
        printf("%s->%d",arg->value,arg->type);
        if(arg->next)
            printf(",");
        arg = arg->next;
    }
    printf("\n");
}

void print_cmds(t_cmd *cmd_list) {
    if(!cmd_list)
    {
        printf("cmd list is empty\n");
        return;
    }
    int cmd_index = 0;
    t_cmd *current_cmd = cmd_list;
    while (current_cmd) {
        printf("Command %d:\n", cmd_index++);
        printf("Command hrdc %d:\n", current_cmd->hrdc_fd);
        print_args(current_cmd->args,"args");
        print_rdr(current_cmd->redir);
        current_cmd = current_cmd->next;
    }
}
