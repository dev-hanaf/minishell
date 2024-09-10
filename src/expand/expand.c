
#include "minishell.h"

t_expand *var(void)
{
	static t_expand head;

	return (&head);
}

void initial_vars(void)
{
	ft_bzero(var(), sizeof(t_expand));
	// TODO allocate str dynamicaly
	var()->str = _malloc(ALLOC * sizeof(char *));
	if (!var()->str)
	{
		perror("malloc");
		return;
	}
	while (var()->i < ALLOC)
		var()->str[(var()->i)++] = NULL;
	var()->i = 0;
}

void end_variable(char *line)
{
	int i;

	i = var()->i;
	if (line[i] != '\'' && line[i] != '"')
	{
		while (line[i] && (line[i] != '\'' && line[i] != '"'))
		{
			var()->i = i;
			i++;
		}
	}
}

void parse_line(char *line, int *start, bool *open_close, int heredoc)
{
	*start = var()->i;
	*open_close = true;
	if (!heredoc &&  line[var()->i] && line[var()->i + 1] && (line[var()->i] == '\'') && (line[var()->i + 1] == '\''))
		var()->i++;
	else if (!heredoc && line[var()->i] && line[var()->i + 1] && (line[var()->i] == '"') && (line[var()->i + 1] == '"'))
		var()->i++;
	else if (!heredoc && line[var()->i] && (line[var()->i] == '\'' || line[var()->i] == '"'))
		*open_close = open_or_close(line);
	else if (line[var()->i] && line[var()->i + 1] && line[var()->i] == '$' && (line[var()->i + 1] == '\'' || line[var()->i + 1] == '"'))
		*start += 1;
	else
		end_variable(line);
}

char **catch_expand(char *line, t_env *env, int flag, int heredoc)
{
	char *str;
	int start;
	bool open_close;
	start = 0;
	open_close = true;
	initial_vars();
	while (line[var()->i])
	{
		parse_line(line, &start, &open_close, heredoc);
		str = ft_substr(line, start, var()->i - start + 1);
		// printf(GREEN"parse line --> %s\n"NC, str);
		if (open_close && ft_strchr(str, '$') && ft_strlen(line) > 1)
			start_expanding(str, env, flag);
		else
			var()->str[var()->y] = ft_strjoin(var()->str[var()->y], str);
		if (line[var()->i] != '\0')
			var()->i++;
	}
	// __exit(NULL);
	return (var()->str);
}

char **expand(t_env *env, char *line)
{
	char **res;
	int i;

	res = NULL;
	i = 0;
	res = catch_expand(line, env, 0, 0);
	while (res[i])
	{
		res[i] = handle_quotes(res[i]);
		i++;
	}
	return (res);
}

char *expand_herdoc(t_env *env, char *line)
{
	char **res;

	res = NULL;
	res = catch_expand(line, env, 1, 1);
	return (res[0]);
}
