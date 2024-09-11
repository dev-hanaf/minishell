#include "minishell.h"
//todo parse the line and execute the command


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
         ft_lstadd_back(&curr_cmd->args, ft_lstnew(tokens->value));
        tokens = tokens->next;
    }
    get_ms()->cmd = cmd;
    if(handle_heredoc(cmd))
		return NULL;
    return cmd;
}
