
#include "minishell.h"

t_expand	*var(void)
{
	static t_expand	head;

	return (&head);
}

void initial_vars(void)
{
	ft_bzero(var(), sizeof(t_expand));
	//TODO allocate str dynamicaly
	var()->str = ft_allocator(ALLOC * sizeof(char *), "expand");
	if (!var()->str)
	{
		perror("malloc");
		return ;
	}
	while (var()->i < ALLOC)
		var()->str[(var()->i)++] = NULL;
	var()->i = 0;
}

void	end_variable(char *line)
{
	int i;

	i = var()->i;
	if (line [i] != '\'' && line[i] != '"')
	{
		while (line[i] && (line [i] != '\'' && line[i] != '"'))
		{
			var()->i = i;
			i++;
		}
	}
}

void parse_line(char *line, int *start, bool *open_close)
{
	*start = var()->i;
	*open_close = true;
	if (line[var()->i] && line[var()->i + 1] && (line[var()->i] == '\'') && (line[var()->i + 1] == '\''))
		var()->i++;
	else if (line[var()->i] && line[var()->i + 1] && (line[var()->i] == '"') && (line[var()->i + 1] == '"'))
		var()->i++;
	else if (line[var()->i] && (line[var()->i] == '\'' || line[var()->i] == '"'))
		*open_close =  open_or_close(line);
	else if (line[var()->i] && line[var()->i + 1] && line[var()->i] == '$' && (line[var()->i + 1] == '\'' || line[var()->i + 1] == '"') )
		*start += 1;
	else
		end_variable(line);
}

char	**catch_expand(char *line, t_env *env, int flag)
{
	char *str;
	int start;
	bool open_close;

	initial_vars();
	while(line[var()->i])
	{
		parse_line(line, &start, &open_close);
		str = ft_substr(line, start, var()->i - start + 1);
		printf(GREEN"to be expanded %d \t\t%s\n"NC,open_close, str);
		if (open_close && ft_strchr(str, '$') && ft_strlen(line) > 1)
			start_expanding(str, env, flag);
		else
			var()->str[var()->y] = ft_strjoin(var()->str[var()->y], str);
		if (line[var()->i] != '\0')
			var()->i++;
	}
	return (var()->str);
}

char	*expand(t_env *env, char *line)
{
	char	**res;
	char	*str;
	int		i;

	str = NULL;
	res = NULL;
	i = 0;
	res = catch_expand(line, env, 1);
	while (res[i])
	{
		res[i] = handle_quotes(res[i]);
		str = ft_strjoin(str, res[i]);
		i++;
	}
	return (str);
}
