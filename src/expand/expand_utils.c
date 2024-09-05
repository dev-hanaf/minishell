#include "minishell.h"

void	add_to_back_expand(t_tokenizer **token, t_tokenizer *new)
{
	t_tokenizer	*temp;

	if ((*token)->value == NULL && (*token)->type == ERROR)
	{
		*token = new;
		return ;
	}
	temp = *token;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

bool is_opend(char c , bool open)
{
	if (c == '"' && !open)
	{
		open = true;
	}
	else if (c == '"' && open)
	{
		open = false;
	}
	return (open);
}

int	needs_expansion(const char *line)
{
	int		i;
	char	hold;

	i = 0;
	hold = 0;
	while (line && line[i])
	{
		if (line[0] == '$' && line[1] == '\0')
			return (0); 
		if (hold == 0 && (line[i] == '\'' || line[i] == '\"'))
			hold = line[i];
		else if (hold != 0 && line[i] == hold)
			hold = 0;
		if (hold != '\'' && line[i] == '$')
			return (1); 
		i++;
	}
	return (0);
}

int	var_need_expansion(const char *line)
{
	int		i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '$')
		{
			i++;
			if (line[i])
			{
				if (ft_isalnum(line[i]) || line[i] == '_' || line[i] == '?' || line[i] == '$')
					return 1;
			}
		}
		else
			i++;
	}
	return (0);
}

t_tokenizer	*new_token_expand(char *value, int type, bool expanded)
{
	t_tokenizer	*new;

	new = ft_allocator(sizeof(t_tokenizer), "new");
	if (!new)
		return (NULL);
	new->value = value;
	new->expanded = expanded;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int get_pid(void)
{
    int pid;

    pid = fork();
    if (pid == CHILD)
	{
        exit(0);
	}
	wait(0);
    return (pid - 2);
}

int valid_expansion_variable(char c)
{
	if (c == '?')
		return (1);
	if (c == '$')
		return (1);
	if (ft_isalnum(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

int counter(char *str, char *seps)
{
	int i;
	int counter;
	
	counter = 0;
	i = 0;
	while (str && str[i] && seps)
	{
		while(str[i] && ft_strchr(seps, str[i]))
			i++;
		if (str && str[i] && !ft_strchr(seps, str[i]))
		{
			counter++;
			while (str && str[i] && !ft_strchr(seps, str[i]))
				i++;
		}
	}
	return (counter);
}

void	start_end(char *str, char *seps, int *start, int *end)
{
	int		index;

	while (str && str[*start] && ft_strchr(seps, str[*start]))
		(*start)++;
	index = *start;
	while (str && str[index] && !ft_strchr(seps, str[index]))
	{
		(*end)++;
		index++;
	}

}

char **ft_split_whitespaces(char *str, char *seps)
{
	int i;
	char **res;
	int start;
	int end;

	i = 0;
	start = 0;
	end = 0;
	res = malloc(sizeof(char *) * (counter(str, seps) + 1));
	if (!res)
		return (NULL);
	while (i < counter(str, seps))
	{
		start_end(str, seps, &start, &end);
		res[i] = ft_substr(str, start, (start + end) - start);
		start += end;
		end = 0;
		i++;
	}
	res[i] = NULL;
	return (res);
}
