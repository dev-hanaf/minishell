#include "libft.h"
#include "minishell.h"

int     _export(t_env **env,t_cmd *cmd,int flag)
{
	(void) cmd;//TODO do something hh
	(void) flag;//TODO do something hh
    if(!env)
        return 0;//i still need to check this
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
