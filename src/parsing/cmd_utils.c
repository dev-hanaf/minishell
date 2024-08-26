#include "minishell.h"
// Function to create a new command
t_cmd* new_cmd() {
    t_cmd *newCmd = (t_cmd*)ft_allocator(sizeof(t_cmd),"parsing");
    if (!newCmd) return NULL;
    newCmd->args = NULL; // Copy the name
    newCmd->next = NULL;
    newCmd->redir = NULL;
    newCmd->heredoc = NULL;
    newCmd->hrdc_fd = -1;
    return newCmd;
}

// Function to add a command to the back of the list
void add_to_back_cmd(t_cmd **head, t_cmd *newCmd) {
    if (*head == NULL) {
        *head = newCmd;
    } else {
        t_cmd *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newCmd;
    }
}
t_cmd *get_last_cmd(t_cmd *head)
{
    if(!head)
        return NULL;
    while(head->next)
        head = head->next;
    return head;
}
int cmd_nbr(t_cmd *head)
{
    int i;

    i = 0;
    while(head)
    {
        i++;
        head = head->next;
    }
    return i;
}
//change this function place
char **ld_to_arr(t_list *lst)
{
	if(!lst)
		return NULL;
	char **arr = ft_allocator(sizeof(char *) * (ft_lstsize(lst) + 1),"parsing");
	int i = 0;
	while(lst)
	{
		arr[i] = ft_strdup((char *)lst->content);
		i++;
		lst = lst->next;
	}
	arr[i] = NULL;
	return arr;
}