/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:48:49 by zmourid           #+#    #+#             */
/*   Updated: 2024/09/14 20:48:50 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
// void print_rdr(t_rdr *redir)
// {
//     while(redir)
//     {
//         if(redir->type == REDIR_IN)
//             dprintf(2,"redir in %s\n",redir->value);
//         if(redir->type == REDIR_OUT)
//             dprintf(2,"redir out %s\n",redir->value);
//         redir = redir->next;
//     }
// }

// void print_args(t_list *arg,char *name)
// {
//     if(!arg)
//         return;
//     printf("%s:",name);
//     while (arg) {
//         printf("%s", (char *)arg->content);
//         if(arg->next)
//             printf(",");
//         arg = arg->next;
//     }
//     printf("\n");
// }

// void print_redir(t_rdr *arg)
// {
//     if(!arg)
//         return;
//     printf("redirections:");
//     while (arg) {
//         printf("%s->%d",arg->value,arg->type);
//         if(arg->next)
//             printf(",");
//         arg = arg->next;
//     }
//     printf("\n");
// }

// void print_cmds(t_cmd *cmd_list) {
//     if(!cmd_list)
//     {
//         printf("cmd list is empty\n");
//         return;
//     }
//     int cmd_index = 0;
//     t_cmd *current_cmd = cmd_list;
//     while (current_cmd) {
//         printf("Command %d:\n", cmd_index++);
//         printf("Command hrdc %d:\n", current_cmd->hrdc_fd);
//         print_args(current_cmd->args,"args");
//         print_rdr(current_cmd->redir);
//         current_cmd = current_cmd->next;
//     }
// }

void print_rdr(t_rdr *redir) { while(redir) {
        if(redir->type == REDIR_IN)
            dprintf(2, "Redirection: \033[0;36mIN\033[0m \t Value: \033[0;35m%s\033[0m\n", redir->value);
        if(redir->type == REDIR_OUT)
            dprintf(2, "Redirection: \033[0;36mOUT\033[0m \t Value: \033[0;35m%s\033[0m\n", redir->value);
        redir = redir->next;
    }
}

void print_args(t_list *arg, char *name) {
    if (!arg)
        return;
    printf("\033[0;34m%s:\033[0m ", name);
    while (arg) {
		printf("\033[0;32m%s\033[0m", (char *)arg->content);
        if (arg->next)
            printf(", ");
        arg = arg->next;
    }
    printf("\n");
}

void print_redir(t_rdr *arg) {
    if (!arg)
        return;
    printf("\033[0;34mRedirections:\033[0m ");
    while (arg) {
        printf("\033[0;33m%s\033[0m -> \033[0;36m%d\033[0m", arg->value, arg->type);
		if(arg->type == HERDOC)
			printf("\033[0;33mheredoc fd\033[0m -> \033[0;36m%d\033[0m", arg->fd);
        if (arg->next)
            printf(", ");
        arg = arg->next;
    }
    printf("\n");
}

void print_cmds(t_cmd *cmd_list) {
    if (!cmd_list) {
        printf("\033[0;31mCommand list is empty\033[0m\n");
        return;
    }
    int cmd_index = 0;
    t_cmd *current_cmd = cmd_list;
    while (current_cmd) {
        printf("\033[0;33mCommand %d:\033[0m\n", cmd_index++);
        printf("\033[0;34mCommand hrdc_fd:\033[0m \033[0;32m%d\033[0m\n", current_cmd->hrdc_fd);
        print_args(current_cmd->args, "Args");
        print_redir(current_cmd->redir);
        current_cmd = current_cmd->next;
        printf("\033[0;36m--------------------------------------------------\033[0m\n");
    }
}
