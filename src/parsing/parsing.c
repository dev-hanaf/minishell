#include "minishell.h"
//todo parse the line and execute the command
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
        if((tokens->type == REDIR_IN || tokens->type == REDIR_OUT) && tokens->next)
        {
            if(tokens->type==REDIR_IN)
                ft_lstadd_back(&curr_cmd->redir_in, ft_lstnew(tokens->next->value));
            if(tokens->type==REDIR_OUT)
                ft_lstadd_back(&curr_cmd->redir_out, ft_lstnew(tokens->next->value));
            tokens = tokens->next->next;
            continue;
        }
        ft_lstadd_back(&curr_cmd->args, ft_lstnew(tokens->value));
        tokens = tokens->next;
    }
    return cmd;
}