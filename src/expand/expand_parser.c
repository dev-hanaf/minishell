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

	spaces = is_space(exp);
	if (spaces && (line[0] != '"'))
	{
		var()->spilted = ft_split_whitespaces(var()->exp, " \t\n\v\f\r");
		var()->x = 0;
		ft_strcpy(var()->buffer, '"');
		var()->str[var()->y] = ft_strjoin(var()->str[var()->y],
			var()->buffer);
		while (var()->spilted[var()->x])
		{
			var()->str[var()->y] = ft_strjoin(var()->str[var()->y],
			var()->buffer);
			var()->str[var()->y] = ft_strjoin(var()->str[var()->y],
			var()->spilted[var()->x]);
			var()->str[var()->y] = ft_strjoin(var()->str[var()->y],
			var()->buffer);
			if (var()->spilted[var()->x + 1] != NULL)
				var()->y++;
			var()->x++;
			var()->str[var()->y] = ft_strjoin(var()->str[var()->y],
			var()->buffer);
		}
	}
	else
	{
		var()->str[var()->y] = ft_strjoin(var()->str[var()->y],
			var()->exp);
	var()->str[var()->y] = ft_strjoin(var()->str[var()->y],
		var()->buffer);
	}
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
		if (line[i] == '$' && line[i + 1] && var_need_expansion(line))
		{
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
