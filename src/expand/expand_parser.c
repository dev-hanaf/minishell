#include "minishell.h"

bool	is_space(char *exp)
{
	int		i;
	bool	spaces;

	spaces = false;
	i = 0;
	while (exp && exp[i])
	{
		if (is_whitespaces(exp[i]))
			spaces = true;
		i++;
	}
	return (spaces);
}

void	whitspaces_in_var(char *exp, char *line)
{
	bool	spaces;
	bool 	there_is_space;

	there_is_space = false;
	spaces = is_space(exp);
	if (spaces && (line[0] != '"'))
	{
		if (is_whitespaces(var()->exp[0]))
			there_is_space = true;
		var()->spilted = ft_split_whitespaces(var()->exp, " \t\n\v\f\r");
		var()->x = 0;
		if (!var()->is_first && there_is_space)
			var()->y++;
		while (var()->spilted[var()->x])
		{
			//ft_strcpy(var()->buffer, '"');
			//var()->str[var()->y] = ft_strjoin(var()->str[var()->y],
				//var()->buffer);
			var()->str[var()->y] = ft_strjoin(var()->str[var()->y],
				var()->spilted[var()->x]);
			//var()->str[var()->y] = ft_strjoin(var()->str[var()->y],
				//var()->buffer);
			if (var()->spilted[var()->x + 1] != NULL)
				var()->y++;
			var()->x++;
		}
	}
	else
	{	 
		//ft_strcpy(var()->buffer, '"');
		//var()->str[var()->y] = ft_strjoin(var()->str[var()->y],
			//	var()->buffer);
		var()->str[var()->y] = ft_strjoin(var()->str[var()->y],
			var()->exp);
		//var()->str[var()->y] = ft_strjoin(var()->str[var()->y],
			//var()->buffer);	
	}
}

char	*add_escape_character(char *var)
{
	int		len;
	int		idx;
	int		jdx;
	char	*new_var;

	len = 0;
	if (!var)
		return (NULL);
	while (var[len])
	{
		if (var[len] == '"' || var[len] == '\'')
			len++;
		len++;
	}
	new_var = _malloc(sizeof(char) * (len + 1));
	if (new_var == NULL)
	{
		//TODO: do something
		__exit(NULL);
	}
	idx = 0;
	jdx = 0;
	while (var[idx])
	{
		if (var[idx] == '"' || var[idx] == '\'')
			new_var[jdx++] = ESCAPE;
		new_var[jdx] = var[idx];
		jdx++;
		idx++;
	}
	new_var[jdx] = '\0';
	return (new_var);
}

void	expansion_valid(char *line, int *i, t_env **env, int flag)
{
	int	start;

	start = *i;
	if (line[*i] && line[*i] == '$')
		(*i)++;
	else if (line[*i] && line[*i] == '?')
		(*i)++;
	else if (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	else if (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
			(*i)++;
	var()->exp = ft_substr(line, start, *i - start);
	var()->exp = get_env(env, var()->exp);
	//TODO: test
	var()->exp = add_escape_character(var()->exp);
	if (var()->exp)
	{
		if (flag)
			var()->str[var()->y] = ft_strjoin(var()->str[var()->y],
				var()->exp);
		else
			whitspaces_in_var(var()->exp, line);
	}
}

void	start_expanding(char *line, t_env *env, int flag)
{
	int	i;

	i = 0;
	while (line[i])
	{
		//N$var$var"$var"
		if (line[i] == '$' && line[i + 1] && var_need_expansion(line))
		{
			
			if (i == 0 && var()->xxx == 0)
				var()->is_first = true;
			// printf(YELLOW"is first %s --->  %d -----> line[%d]=%c  && var()->xxx = %d\n\n\n\n"NC, line, var()->is_first, i , line[i], var()->xxx);
			i++;
			expansion_valid(line, &i, &env, flag);
			continue ;
		}
		else
		{
			ft_strcpy(var()->buffer, line[i]);
			var()->str[var()->y] = ft_strjoin(var()->str[var()->y],
				var()->buffer);
		}
		if (line[i] != '\0')
			i++;
	}
	var()->xxx++;
}

bool	open_or_close(char *line)
{
	char	to_find;
	int		i;

	i = var()->i;
	to_find = 0;
	while (line && line[i])
	{
		if ((line[i] == '"' || line[i] == '\'') && !to_find)
		{
			to_find = line[i];
			i++;
		}
		while (line[i] && line[i] != to_find && to_find)
		{
			i++;
			var()->i = i;
		}
		if (to_find == '\'')
			return (false);
		else if (to_find == '"')
			return (true);
		if (line[i] != '\0')
			i++;
	}
	return (true);
}
