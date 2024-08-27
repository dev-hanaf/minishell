
#include "minishell.h"

#define ALLOC 10

t_expand *var(void)
{
	static t_expand head;
	return (&head);
}

void	should_expand(char *line, int to_expand, t_env *env)
{
	if (line[var()->i + 1] && ft_isdigit(line[var()->i + 1]))
	{
		var()->i += 2;
		should_expand(line, to_expand, env);
	}
	var()->start = var()->i;
	var()->i++;
	while (line[var()->i] && line[var()->i] != '$' && (ft_isalnum(line[var()->i]) || line[var()->i] == '_')
		&& !is_whitespaces(line[var()->i]))
		var()->i++;
	var()->exp = ft_substr(line, var()->start, var()->i - var()->start);
	var()->exp = get_env(&env, var()->exp + 1);
	printf("exp ==> %s\n", var()->exp);
	var()->j = 0;
	var()->space = false;
	while (var()->exp && var()->exp[var()->j])
	{
		if (is_whitespaces(var()->exp[var()->j]))
			var()->space = true;
		var()->j++;
	}
	if (var()->space && !var()->open)
	{
		var()->spilted = ft_split(var()->exp, ' ');
		var()->y = 0;
		while (var()->spilted[var()->y])
		{
			var()->str[var()->exp_cmpt] = ft_strjoin(var()->str[var()->exp_cmpt], var()->spilted[var()->y]);
			if (var()->spilted[var()->y + 1] != NULL)
				var()->exp_cmpt++;
			var()->y++;
		}
	}
	else if (var()->exp)
		var()->str[var()->exp_cmpt] = ft_strjoin(var()->str[var()->exp_cmpt],var()-> exp);
}


char	**catch_expand(char *line, t_env *env, int to_expand)
{
	ft_bzero(var(), sizeof(t_expand));
	//TODO allocate str dynamicaly
	var()->str = ft_allocator(ALLOC * sizeof(char *), "expand");
	if (!var()->str)
	{
		perror("malloc");
		return (NULL);
	}
	while (var()->i < ALLOC)
		var()->str[(var()->i)++] = NULL;
	var()->i = 0;
	if (line && ft_strchr(line, '$'))
	{
		while (line[var()->i])
		{ //TODO $_ is not expandig
			var()->open = is_opend(line[var()->i], var()->open);
			if (line[var()->i] && to_expand && line[var()->i] == '$' && line[var()->i]
				&& (ft_isalnum(line[var()->i + 1]) || line[var()->i] == '_'))
			{
				should_expand(line, to_expand, env);
				continue ;
			}
			else if (line[var()->i + 1] && line[var()->i] == '$' && ft_isdigit(line[var()->i + 1]))
			{
				//$9HOME ==> HOME
				var()->i += 2;
				continue ;
			}
			else if (line[var()->i] && var()->i > 0 && line[var()->i] == '$' && line[var()->i - 1] == '"'
					&& line[var()->i + 1] == '"')
			{
				//"$"HOME ==> $HOME
				usleep(1);
				//TODO pass();
			}
			else if (line[var()->i] && line[var()->i] == '$' && line[var()->i + 1] && (line[var()->i + 1] == '\'' || line[var()->i + 1] == '\"'))
			{
				//skip dollar $"HOME" ==> HOME
				var()->i++;
				continue ;
			}
			else if (line[var()->i] && line[var()->i] == '$' && !ft_isalnum(line[var()->i + 1]))
			{
				// $%HOME ==> $%HOME
				ft_strcpy(var()->buffer, line[var()->i]);
				var()->str[var()->exp_cmpt] = ft_strjoin(var()->str[var()->exp_cmpt], var()->buffer);
				var()->i++;
				continue ;
			}
			else if (line[var()->i] == '\'' && var()->open == false)
			{
				ft_strcpy(var()->buffer, line[var()->i]);
				var()->str[var()->exp_cmpt] = ft_strjoin(var()->str[var()->exp_cmpt], var()->buffer);
				var()->i++;
				while (line[var()->i]  && line[var()->i] != '\'')
				{
					printf("%c\n", line[var()->i]);
					ft_strcpy(var()->buffer, line[var()->i]);
					var()->str[var()->exp_cmpt] = ft_strjoin(var()->str[var()->exp_cmpt], var()->buffer);
					var()->i++;
				}
				if (line[var()->i] == '\'')
				{
					ft_strcpy(var()->buffer, line[var()->i]);
					var()->str[var()->exp_cmpt] = ft_strjoin(var()->str[var()->exp_cmpt], var()->buffer);
					var()->i++;
				}
				continue;
			}
			ft_strcpy(var()->buffer, line[var()->i]);
			var()->str[var()->exp_cmpt] = ft_strjoin(var()->str[var()->exp_cmpt], var()->buffer);
			if (line[var()->i] == '\0')
				break ;
			var()->i++;
		}
	}
	var()->exp_cmpt++;
	return (var()->str);
}

t_tokenizer	*expand_lexer(t_env *env, t_tokenizer **lexer)
{
	char		**res;
	int			to_expand;
	t_tokenizer	*temp;
	t_tokenizer	*head;
	int			i;
	t_tokenizer	*new;

	to_expand = 0;
	temp = *lexer;
	head = new_token(NULL, 0);
	while (temp)
	{
		i = 0;
		if (temp->prev && temp->prev->type == HERDOC)
		{
			new = new_token(temp->value, temp->type);
			add_to_back_expand(&head, new);
		}
		else
		{
			to_expand = needs_expansion(temp->value);
			res = catch_expand(temp->value, env, to_expand);
			while (res[i])
			{
				//printf(MAGENTA"res[%d] ==> %s\n"NC,i, res[i]);
				i++;
			}
			i = 0;
			if (to_expand)
			{
				if (!res[i])
				{
					new = new_token(NULL, WORD);
					add_to_back_expand(&head, new);
				}
				while (res[i])
				{
					new = new_token(handle_quotes(res[i]), WORD);
					add_to_back_expand(&head, new);
					i++;
				}
			}
			else
			{
				if (res[0])
				{
					new = new_token(handle_quotes(res[0]), temp->type);
					add_to_back_expand(&head, new);
				}
				else
				{
					new = new_token(handle_quotes(temp->value), temp->type);
					add_to_back_expand(&head, new);
				}
			}
		}
		temp = temp->next;
	}
	return (head);
}

char	*expand(t_env *env, char *line)
{
	int		to_expand;
	char	**res;
	char	*str;
	int		i;
	//line = "hello\n$aloha\nbroski\n$HOME";
	//TODO you dommy need to expand the line if it has $ in it
	to_expand = 0;
	str = NULL;
	res = NULL;
	i = 0;
	to_expand = needs_expansion(line);
	res = catch_expand(line, env, to_expand);
	while (res[i])
	{
		res[i] = handle_quotes(res[i]);
		str = ft_strjoin(str,res[i]);
		i++;
	}
	return (str);
}

/* ''''''$HOME''''''  | "''"''$HOME''"''" | ''''$HOME'"' | $"''"'''''$HOME'''''"''" |  $USER"v" | $+HOME  | $HOME$HOME |  $HOME$HOM  */
//TODO echo ''''''$HOME'''''' ==> /nfs/homes/ahanaf

// TODO echo "''"''$HOME''"''" ==> ''/nfs/homes/ahanaf''

// TODO  echo ''''$HOME'"' ==> /nfs/homes/ahanaf"

// TODO  echo $"''"'''''$HOME'''''"''" ==> ''$HOME''

//TODO $USER"v" ==> ahanafv

//TODO '""$USER""'

//TODO   $+HOME =====> $+HOME

// TODO $HOME$HOME ===> /nfs/homes/ahanaf/nfs/homes/ahanaf

// TODO $HOME$HOM ==>  /nfs/homes/ahanaf

//TODO  "$"HOME ==> $HOME

//TODO after export arg="ls -la"; then axpand $arg the result should be as followd ==> [ls][-la]
//TODO after export arg="ls -la"; then axpand "$arg" the result should be as followd ==> [ls -la]

/*  if (line[i] && to_expand && line[i] == '$' && line[i + 1] && line[i
		+ 1] == '?')
    {
        char *exp = ft_itoa(g_minishell.status);
        line = ft_strjoin(ft_substr(line, 0, i), exp);
        line = ft_strjoin(line, ft_substr(line, i + 2, ft_strlen(line) - i
			- 2));
    } */
