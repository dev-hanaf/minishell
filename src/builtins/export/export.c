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
int str_is_valid(char *str)
{
    int i;
    i = 0;
    if(!str || !*str)
        return 0;
    while(str[i] && str[i] != '=')
    {
        if(ft_isalnum(str[i]) == 0)
        {
            if(str[i] == '+' && str[i+1] == '=')
                return 2;
            return 0;
        }
        i++;
    }
    return 1;
}
void process_args(char *str)
{
    char *key;
    char *value;
    if(!str)
        return;
    int flag = str_is_valid(str);
    if(flag == 0)
    {
        dprintf(2,"ms: export: `%s': not a valid identifier\n",str);
        return;//TODO handle exit status here mate
    }
    else
    {
        printf("%s\n",str);
        printf("%s\n",ft_strchr(str,'=') + 1);
        printf("%s\n",ft_substr(str,0,ft_strchr(str,'=') - str));
    }
}
int     _export(t_env **env,t_list *args)
{
    if(!env)
        return 0;//i still need to check this
    //display_environment(env);
    if(!args)
        print_export(*env);
    while(args)
    {
        process_args(args->content);
        args = args->next;
    }
	return 0;
}

//int main(int ac ,char **av, char **envp)
//{
//    t_env *env = init_envirement(envp);
//    g_minishell.env = envp;
//    add_to_back_env(&env, new_env(ft_strdup("aloha"), ft_strdup("bonjour")));
//    display_envirment(&env);
//    t_cmd *cmd = new_cmd();
//	_export(&env);
//}
