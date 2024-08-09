#include "minishell.h"
void print_args(t_list *arg,char *name)
{
    if(!arg)
        return;
    printf("    %s:",name);
    while (arg) {
        printf("%s", (char *)arg->content);
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
        print_args(current_cmd->args,"args");
        print_args(current_cmd->redir_in,"redir_in");
        print_args(current_cmd->redir_out,"redir_out");
        current_cmd = current_cmd->next;
    }
}
