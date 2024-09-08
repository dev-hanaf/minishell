#include "minishell.h"
// Function to create a new command
t_cmd* new_cmd() {
    t_cmd *newCmd = (t_cmd*)_malloc(sizeof(t_cmd));
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
// TODO change this function place
char **ld_to_arr(t_list *lst)
{
	if(!lst)
		return NULL;
	char **arr = _malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
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

char **env_to_arr(t_env *env)
{
    char *temp;
    temp = NULL;
	if(!env)
		return NULL;
	char **arr = _malloc(sizeof(char *) * (env_size(env) + 1));
	int i = 0;
	while(env)
	{
        temp = ft_strjoin(ft_strdup(env->key),"=");
        temp = ft_strjoin(temp,ft_strdup(env->value));
        if(!temp)//TODO check why there is a problem here
            temp = ft_strdup("");
        arr[i] = temp;
        env = env->next;
		i++;
	}
	arr[i] = NULL;
	return arr;
}