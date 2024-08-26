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

int     _export(t_env **env,t_list *args)
{
    if(!env)
        return 0;//i still need to check this
    display_environment(env);
    if(!args)
        print_export(*env);
    printf("hello world this is export mates\n");
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
