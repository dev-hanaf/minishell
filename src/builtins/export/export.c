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
t_env **clone_env(t_env *env)
{
    t_env **new;
    new = ft_allocator(sizeof(t_env *),"garbage");
    if(!new)
    {
        perror("malloc"); //TODO add exit and free all
        exit(1);
    }
    *new = NULL;
    while(env)
    {
        add_to_back_env(new,new_env(env->key,env->value));
        env = env->next;
    }
    return new;
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
        *value = ft_strdup(ft_strchr(str,'=') + 1);
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
    node = get_env_ld(get_ms()->env_ld,key);
    if(!node)
    {
        add_to_back_env(get_ms()->env_ld,new_env(key,value));
        return ;
    }
    if(concat)
        value = ft_strjoin(node->value,value);
    if(node)
    {
        if(value)
            node->value = value;
        return;
    }
    add_to_back_env(get_ms()->env_ld,new_env(key,value));
}
int process_args(char *str)
{
    //printf("%s\n",str);
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
         return 0;//TODO handle exit status here mate
     }
     else
     {
        fill_key_value(str,&key,&value,flag- 1);
        make_and_add(key,value,flag - 1);
        //printf("%s\n",str);
        //printf("key=%s,",key);
        //printf("value=%s\n",value);
     }
     return 1;
}
int     _export(t_env **env,t_list *args)
{
    int status;
    status = 0;
    if(!env)
        return 0;// TODO i still need to check this
    //display_environment(env);
    //printf("hello im export content = %s\n",(char *)args->content);
    if(!args)
        print_export(*env);
    while(args)
    {
        if(!process_args(args->content))
            status = 1;
        args = args->next;
    }
	return status;
}
