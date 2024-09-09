#include "libft.h"
#include "minishell.h"

void print_export(t_env *env)
{

    while(env)
    {
        printf("declare -x %s",env->key);
        if(env->value)
            printf("=\"%s\"",env->value);
        printf("\n");
        env = env->next;
    }
}

t_env *sort_list(t_env* lst) {
    char *key;
	char *value;
	key = NULL;
	value = NULL;
    t_env *start;

    start = lst;

    while (lst != NULL && lst->next != NULL)
    {
        if (ft_strcmp(lst->key, lst->next->key) >= 0)
		{
            key = lst->key;
			value = lst->value;
			lst->key = lst->next->key;
			lst->value = lst->next->value;
			lst->next->key = key;
			lst->next->value = value;
			lst = start;
        }
	else
		lst = lst->next;
    }
    return (start);
}
t_env *clone_env(t_env *env)
{
    t_env **new;
    new = _malloc(sizeof(t_env *));
    if(!new)
    {
        perror("malloc"); //TODO add exit and free all
        clean_exit(1);
    }
    *new = NULL;
    while(env)
    {
        add_to_back_env(new,new_env(env->key,env->value));
        env = env->next;
    }
    return sort_list(*new);
}
int key_is_valid(char *str)
{
    int i = 0;
    if(!str || !*str || (!ft_isalpha(*str) && *str != '_'))
        return 0;
    while(str[i])
    {
        if(ft_isalnum(str[i]) == 0 && str[i] != '_')
            return 0;
        i++;
    }
    return 1;
}
int str_is_valid(char *str)
{
    int i;
    i = 0;
    if(!str || !*str || (!ft_isalpha(*str) && *str != '_'))
        return 0;
    while(str[i] && str[i] != '=')
    {
        if(ft_isalnum(str[i]) == 0 && str[i] != '_')
        {
            if(ft_strchr(str,'=') && str[i] == '+' && str[i+1] == '=')
                return 2;
            return 0;
        }
        i++;
    }
    return 1;
}
void fill_key_value(char *str,char **key,char **value,int flag)
{ 
	//check with the values passed should i be freed or not 
    if(ft_strchr(str,'='))
    {
        *value = ft_strdup_env(ft_strchr(str,'=') + 1);
        //printf("len = %ld\n",ft_strchr(str,'=') - str  - flag );
        *key = ft_substr(str,0,ft_strchr(str,'=') - str - flag);
        return;
    }
    *key = str;
    *value = NULL;
}
void make_and_add(char *key,char *value,int concat)
{
    t_env *node;
	key = ft_strdup_env(key);
	value = ft_strdup_env(value);
    node = get_env_ld(get_ms()->env_ld,key);
    if(!node)
    {
        add_to_back_env(get_ms()->env_ld,new_env(key,value));
        return ;
    }
    if(concat)
        value = ft_strjoin_env(node->value,value);
    if(node)
    {
        if(value)
            node->value = value;
        return;
    }
	//dprintf(2,"key=%s\n",key);
	//dprintf(2,"value=%s\n",value);
    add_to_back_env(get_ms()->env_ld,new_env(key,value));
}

int process_args(char *str)
{
     char *key;
     char *value;
     key = NULL;
     value = NULL;
     int flag;
     flag = 1;
     flag = str_is_valid(str);
     if(!str)
         return 0;
     if(flag == 0)
     {
         dprintf(2,"ms: export: `%s': not a valid identifier\n",str);
			update_status(1);
         return 0;//TODO handle exit status here mate
     }
     else
     {
        fill_key_value(str,&key,&value,flag- 1);
        make_and_add(key,value,flag - 1);
     }
     return 1;
}
void process_nodes(t_env *env,char *arg)
{
	char *key = NULL;
	char *value = NULL;
	char c[2];
	int i;
	char **strs;

	strs = NULL;
	i = 0;
	while (arg && arg[i] && arg[i] != '=')
	{
		ft_strcpy(c, arg[i]);
		key = ft_strjoin(key, c);
		i++;
	}
	if (arg && arg[i] == '=')
		i++;
	while (arg && arg[i])
	{
		ft_strcpy(c, arg[i]);
		value = ft_strjoin(value, c);
		i++;
	}
	if (!key ||  (key[0] == '\0'|| ft_strchr(key, '$')))
	{
		dprintf(2, "key ==> %s\t\t value ==> %s\n", key, value);
		dprintf(2, RED"split ALL\n"NC);
		strs = expand(env, arg);
	}
	else
	{
		dprintf(2, "key ==> %s\t\t value ==> %s\n", key, value);
		dprintf(2, GREEN"join ALL\n"NC);
        char *res = NULL;
        ft_strcpy(c, '"');
        res = ft_strjoin(res, c);
		strs = catch_expand(arg, env, 1, 0);
        printf("strs[0] = %s\n",strs[0]);
		int j = 0;
		while (strs[j])
		{
            res = ft_strjoin(res, strs[j]);
            res = ft_strjoin(res, c);
            printf("res = %s\n",res);
            res = handle_quotes(res);
            strs[j] = res;
			j++;
		}
	}
    while(strs && *strs)
    {
		//printf("creating %s\n",*strs);
        if(!process_args(*strs))
        {
        	update_status(1);
        	return;
        }
		strs++;
    }
}

char **export_v2(t_env *env,char  **args)
{
    int i = 0;
	while(args[i])
	{
		process_nodes(env,args[i]);
        i++;
	}
	return NULL;
}

int     _export(t_env **env,char **args)
{
    int status;
    status = 0;
	if(!args)
		return 0;
	args = args + 1;
    if(!args || !*args)
	{
        print_export(sort_list(clone_env(*env)));
	}
	export_v2(*env,args);
    if(!env)
    {
        return 0;// TODO i still need to check this
    }
	return status;
}
